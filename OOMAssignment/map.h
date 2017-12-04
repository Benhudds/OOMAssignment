#pragma once
#include "mapit.h"
#include "exceptions.h"

// Templated pair type
template<typename T1, typename T2>
class pair
{
private:
public:
	// First value
	T1 first;

	// Second value
	T2 second;

	// Self typedef
	typedef pair<T1, T2> self_type;

	// Constructor called when only a key is given
	explicit pair(T1 newFirst) : first(newFirst) { }

	// Constructor called with key and value
	pair(T1 newFirst, T2 newSecond) : first(newFirst), second(newSecond) { }

	// Copy constructor
	pair(const pair &obj) : first(obj.first), second(obj.second) { }

	// Default contructor
	pair() : first(), second() { }

	// Destructor
	~pair() { }

	// Assignment operator - copy
	self_type& operator=(const self_type& other)
	{
		first = other.first;
		second = other.second;
		return *this;
	}

	// Assignment operator - value mutation
	self_type& operator=(T2 value)
	{
		this.second = value;
		return *this;
	}
};

// Templated comparison function pointer
template<class KT>
using cmp = bool(*)(KT k1, KT k2);

// Default less than comparison operation
template<class KT>
bool less(KT a, KT b)
{
	return a < b;
}

// Templated allocator function pointer
template<class T1, class T2>
using alloc = pair<T1, T2>*(*)(const size_t size);

// Default allocation method
template<class T1, class T2>
pair<T1, T2>* allocate(const size_t size)
{
	return new pair<T1, T2>[size];
}

// Templated deallocator function pointer
template<class T1, class T2>
using dealloc = void(*)(pair<T1, T2>* pt);

// Default deallocation method
template<class T1, class T2>
void deallocate (pair<T1, T2>* pt)
{
	delete[] pt;
}

// Templated map class
template <class KT, class VT>
class map
{
	// Typedefs
public:
	// Key type
	typedef KT key_type;

	// Value type
	typedef VT value_type;
	
	// Self type
	typedef map<KT, VT> self_type;

	// Iterator typedef
	typedef mapit<KT, VT> iterator;

	// Type to be stored by the map
	typedef pair<KT, VT> element_type;

	// Size type typedef
	// Uses size_t for greater indexing ranges when unsigned int may be too small (ie. on 64bit machines)
	typedef size_t size_type;

	// Allocator deallocator pair used to specify memory management method
	typedef pair<alloc<KT, VT>, dealloc<KT, VT>> allocator_pair_type;

	//Friendships
public:
	// Allows iterator access to private operators
	friend iterator;

	// Private members
private:
	// Comparison function reference
	// Required to return a bool with value true if the first element should precede the second
	cmp<KT> comparator;

	// Allocator function reference
	// Required to let the user use a custom allocation method, ie. new or persistence
	alloc<KT, VT> allocator;

	// Deallocator function reference
	// Required to let the user deallocate
	dealloc<KT, VT> deallocator;

	// Array of elements
	// Initialized in constructor
	element_type * elements;

	// Internal array size
	// Defaults to value 10
	size_type arrsize = 10;

	// Number of elements currently in the map
	size_type numElements = 0;

	// Constructors
public:	
	// Default constructor
	// Uses the less than operator for comparison
	map()
	{
		comparator = less;
		allocator = allocate;
		deallocator = deallocate;

		// Initialise the array with the default size of 10
		elements = try_allocate(arrsize);
	}

	// Constructor
	// Takes size the map should assume on creation
	explicit map(const size_type size)
	{
		comparator = less;
		allocator = allocate;
		deallocator = deallocate;

		arrsize = size;
		elements = try_allocate(arrsize);
	}

	// Constructor
	// Takes an allocator deallocator pair
	explicit map(const allocator_pair_type pair)
	{
		comparator = less;
		allocator = pair.first();
		deallocator = pair.second();

		// Initialise the array with the default size of 10
		elements = try_allocate(arrsize);
	}

	// Constructor
	// Takes size the map should assume on creation and allocator deallocator pair
	map(const size_type size,  const allocator_pair_type pair)
	{
		comparator = less;
		allocator = pair.first();
		deallocator = pair.second();

		arrsize = size;
		elements = try_allocate(arrsize);
	}

	// Constructor
	// Takes a comparison operator given by the user
	explicit map(const cmp<KT> cmp)
	{
		comparator = cmp;
		allocator = allocate;
		deallocator = deallocate;

		// Initialise the array with the default size of 10
		elements = try_allocate(arrsize);
	}

	// Constructor
	// Takes a comparison operator given by the user and allocator deallocator pair
	map(const cmp<KT> cmp, const allocator_pair_type pair)
	{
		comparator = cmp;
		allocator = pair.first();
		deallocator = pair.second();

		// Initialise the array with the default size of 10
		elements = try_allocate(arrsize);
	}

	// Constructor
	// Takes a comparison operator given by the user and size the map should assume on creation
	map(const cmp<KT> cmp, const size_type size)
	{
		comparator = cmp;
		allocator = allocate;
		deallocator = deallocate;

		arrsize = size;
		// Initialise the array
		elements = try_allocate(arrsize);
	}

	// Constructor
	// Takes a comparison operator given by the user, allocator deallocator pair, and size the map should assume on creation
	map(const cmp<KT> cmp, const size_type size, const allocator_pair_type pair)
	{
		comparator = cmp;
		allocator = pair.first();
		deallocator = pair.second();

		arrsize = size;
		// Initialise the array
		elements = try_allocate(arrsize);
	}

	// Copy constructor
	map(const self_type& other)
	{
		comparator = other.comparator;
		allocator = other.allocator;
		deallocator = other.deallocator;

		arrsize = other.arrsize;
		numElements = other.numElements;

		elements = try_allocate(arrsize);

		for(size_type i = 0; i < numElements; i++)
		{
			elements[i] = other.elements[i];
		}
	}

	// Destructor
	~map()
	{
		try_deallocate(elements);
	}

	// Operators
private:
	// Array operator
	// Returns element type (pair<KT, VT>) at the given index in the array
	// For use by the iterator, hence private and accessed by friendship
	element_type& operator[](const size_t index)
	{
		return elements[index];
	}

	// Operators
public:
	// Array operator
	// Finds the item if it exists in the map
	// Creates a new item without a key for assignment if it does not
	// Throws user_comparison_function_exception
	value_type& operator[](const key_type key)
	{
		return findOrInsert(key, 0, numElements);
	}

	// Assignment operator
	self_type& operator=(const self_type& other)
	{
		// Copy comparison function
		comparator = other.comparator;

		// Copy new data to a new array
		element_type * newElements = try_allocate(other.arrsize);

		for(size_type i = 0; i < other.numElements; i++)
		{
			newElements[i] = other.elements[i];
		}

		// Destroy old data and deallocate
		try_deallocate(elements);

		// Set data to new array and copy counters
		elements = newElements;
		numElements = other.numElements;
		arrsize = other.arrsize;

		return *this;
	}

	// Private methods
private:
	// Comparator method
	// Called when using the comparison function, be it less or one defined by the user
	// Required in cases where the user defined function throws an exception
	// Throws user_comparison_function_exception
	// Should not compile if operator< not implemented for key_type
	bool comp(key_type first, key_type second)
	{
		try
		{
			return comparator(first, second);
		}
		catch (...)
		{
			throw user_comparison_function_exception();
		}
	}

	// Allocate method
	// Called when using the allocator function
	// Required as the allocator is user defined code
	// Throws bad_allocation_exception
	element_type* try_allocate(const size_type size)
	{
		try
		{
			return  allocator(size);
		}
		catch (...)
		{
			throw bad_allocation_exception();
		}
	}

	// Deallocate method
	// Called when using the deallocator function
	// Required as deallocator is user defined code
	// Throws bad_deallocation_exception
	void try_deallocate(element_type* pt)
	{
		try
		{
			deallocator(pt);
		}
		catch (...)
		{
			throw bad_deallocation_exception();
		}
	}

	// Recursive insert method
	// Recursively searches for the position the element needs to be saved at
	// Inserts the element at that position
	pair<iterator, bool> insert(key_type key, value_type value, const size_type first, const size_type last)
	{
		// Base case - reached an array of size 1
		// This could potentially by the correct key so we must check
		// If it is not we need to break out after the check
		bool lastPass = false;
		if (last - first <= 1)
		{
			lastPass = true;
		}

		// Recursive case
		// Find midpoint
		const size_type mid = first + (last - first) / 2;

		// Split the array and recurse down the correct half
		if (!comp(elements[mid].first, key))
		{
			// Equality check
			if (!comp(key, elements[mid].first))
			{
				// Return iterator and failure to insert
				return pair<iterator, bool>(iterator(this, mid), false);
			}

			// Recurse left
			return lastPass == true ? insert(first, key, value) : insert(key, value, first, mid);
		}

		// Recurse right
		return lastPass == true ? insert(last, key, value) : insert(key, value, mid, last);
	}

	// Method that inserts an item at the given index with the given key and value
	// Returns an iterator to the item and a true bool indicating it has been inserted
	pair<iterator, bool> insert(size_type index, key_type key, value_type value)
	{
		insertElement(index, key, value);
		return pair<iterator, bool>(iterator(this, index), true);
	}

	// Method that returns the value type associated to the given key
	// If the key does not exist in the map then a new element type is created
	// New element type has default unassigned value type
	value_type& findOrInsert(key_type key, const size_type first, const size_type last)
	{
		// Base case - reached an array of size 1
		// This could potentially by the correct key so we must check
		// If it is not we need to break out after the check
		bool lastPass = false;
		if (last - first <= 1)
		{
			lastPass = true;
		}

		// Recursive case
		// Find midpoint
		const size_type mid = first + (last - first) / 2;

		// Split the array and recurse down the correct half
		if (!comp(elements[mid].first, key))
		{
			// Equality check
			if (!comp(key, elements[mid].first))
			{
				// Return value
				return elements[mid].second;
			}

			// Recurse left
			return lastPass == true ? insertElement(first, key) : findOrInsert(key, first, mid);
		}

		// Recurse right
		return lastPass == true ? insertElement(last, key) : findOrInsert(key, mid, last);
	}

	// Method to insert a new element type using the given key and the index
	// Returns a value type with default value
	value_type& insertElement(const size_type index, key_type key)
	{
		// Ensure there is space to insert
		checkSizeAndExpand();

		// Start by shuffling up all the remaining elements
		shuffleUp(index);

		// Insert a new element with nullptr as value and then return
		elements[index] = element_type(key);
		numElements++;
		return elements[index].second;
	}

	// Method to insert a new element type using the given key, value and the index
	// Returns a value type with the given value
	value_type& insertElement(const size_type index, key_type key, value_type value)
	{
		// Ensure there is space to insert
		checkSizeAndExpand();

		// Start by shuffling up all the remaining elements
		shuffleUp(index);

		// Insert a new element with nullptr as value and then return
		elements[index] = element_type(key, value);
		numElements++;
		return elements[index].second;
	}

	// Method to check the size of the array is within bounds
	// Expands the array if necessary
	void checkSizeAndExpand()
	{
		// If the array is full
		if (numElements == arrsize)
		{
			// Expand the array
			arrsize *= 2;

			element_type * newArr = try_allocate(arrsize);

			// Copy the contents and delete the old values
			for (size_type i = 0; i < arrsize / 2; i++)
			{
				newArr[i] = elements[i];
			}

			// Delete the old reference
			try_deallocate(elements);

			// Replace with new array reference
			elements = newArr;
		}
	}

	// Method that shuffles up the elements at the pivotal point by one place
	void shuffleUp(const size_type pivot)
	{
		// Shuffle the elements up from the current position
		for (size_type j = numElements; j > pivot; j--)
		{
			elements[j] = elements[j - 1];
		}
	}

	// Method that shuffles down the elements at the pivotal point by one place
	void shuffleDown(const size_type pivot)
	{
		// Shuffle the elements from the current position
		for (size_type j = pivot; j < numElements; j++)
		{
			elements[j] = elements[j + 1];
		}
	}

	// Binary search for an element with the given key
	// Returns an iterator to that element
	// Returns an iterator to end if it does not exist
	iterator binarySearch(key_type key, const int first, const int last)
	{
		// Base case - reached an array of size 1
		// This could potentially by the correct key so we must check
		// If it is not we need to break out after the check
		bool lastPass = false;
		if (last - first <= 1)
		{
			lastPass = true;
		}

		// Recursive case
		// Find midpoint
		const size_type mid = first + (last - first) / 2;

		// Split the array and recurse down the correct half
		if (!comp(elements[mid].first, key))
		{
			// Equality check
			if (!comp(key, elements[mid].first))
			{
				// Return value
				return iterator(this, mid);
				//return elements[mid];
			}

			// Recurse left
			return lastPass == true ? end() : binarySearch(key, first, mid);
		}

		// Recurse right
		return lastPass == true ? end() : binarySearch(key, mid, last);
	}

	// Public methods
public:
	// Returns an iterator at the beginning of the collection
	iterator begin()
	{
		return iterator(this, 0);
	}

	// Returns an iterator at the end of the collection
	iterator end()
	{
		return iterator(this, size());
	}

	// Returns an iterator at the beginning of the reverse collection
	iterator rbegin()
	{
		return iterator(this, -1);
	}

	// Returns an iterator at the end of the reverse collection
	iterator rend()
	{
		return iterator(this, size() - 1);
	}

	// Returns the number of elements in the array
	size_t size() const {
		return numElements;
	}

	// Returns the size of the array used for storing the map
	size_type arraysize() const
	{
		return arrsize;
	}

	// Method that returns an iterator to the element with the given key
    // Throws user_comparison_function_exception
	iterator find(key_type key)
	{
		return binarySearch(key, 0, numElements);
	}

	// Method that erases the item at the position given by the current iterator
	// Throws an out_of_range_exception if out of range
	iterator erase(const iterator it)
	{
		if (it.pos < 0 || it.pos >= numElements)
		{
			throw out_of_range_exception();
		}
		
		shuffleDown(it.pos);
		numElements--;
		
		return iterator(this, it.pos);
	}

	// Method that erases the element for the given key
	// Returns 1 if erased
	// Returns 0 if not (does not exist)
	// Throws user_comparison_function_exception
	size_type erase(const KT& key)
	{
		iterator pair = find(key);

		if (pair != end())
		{
			shuffleDown(pair.pos);
			numElements--;
			return 1;
		}

		return 0;
	}

	// Method that clears all elements from the map
	// Destroys all elements
	// Recreates empty map with same arraysize
	void clear() noexcept
	{
		try_deallocate(elements);
		elements = try_allocate(arrsize);

		numElements = 0;
	}

	// Method to insert a new element
	// Throws user_comparison_function_exception
	pair<iterator, bool> insert(key_type key, value_type value)
	{
		return insert(key, value, 0, numElements);
	}

	// Method to shrink the size of the array to the number of elements currently stored in it
	void shrinkToFit()
	{
		arrsize = numElements == 0 ? 1 : numElements;

		// Create the new array
		element_type* newArr = try_allocate(arrsize);

		// Copy the data
		for (size_type i = 0; i < numElements; i++)
		{
			newArr[i] = elements[i];
		}

		// Delete old memory objects
		try_deallocate(elements);

		// Replace with new array reference
		elements = newArr;
	}
};