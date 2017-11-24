#pragma once
#include "stdafx.h"
#include "mapit.h"

template<typename KT, typename VT>
class pair
{
private:
public:
	KT key;
	VT value;
	typedef pair<KT, VT> maptype;

	//pair(KT const & newKey, VT const & newValue) : key(newKey), value(newValue) {}
	pair(KT newKey) : key(newKey)
	{
		//key = new KT(newKey);

	}

	pair(KT newKey, VT newValue) : key(newKey), value(newValue)
	{
		//key = new KT(newKey);
		//key = new KT;
		//key = &newKey;

		//value = new VT(newValue);
		/*value = new VT;
		value = &newValue;*/
	}

	pair (const pair &obj) : key(obj.key), value(obj.value)
	{
		/*key = new KT;
		*key = *obj.key;

		value = new VT;
		*value = *obj.value;*/
	}

	pair() : key(), value()
	{
		//key = new KT;
		//key = nullptr;

		//value = new VT;
		//value = nullptr;
	}

	~pair()
	{
		/*delete key;
		delete value;*/
	}
	//CTwoInts CTwoInts::operator = ( CTwoInts operand )
	//pair<KT, VT> operator=(pair<KT, VT> newPair) { key = newPair->key, value = newPair->value; return *this; }
	/*pair<KT, VT> operator=(pair<KT, VT>* newPair)
	{
		key = newPair->key;
		value = newPair->value;
		return *this;
	}*/

	//pair<KT, VT>& operator=(pair<KT, VT>* other);
	pair<KT, VT>& operator=(const pair<KT, VT>& other);

	pair<KT, VT>& operator=(VT value)
	{
		this.value = value;
		return *this;
	}

	/*pair<KT, VT>& operator=(const pair<KT, VT> newPair) { key = newPair->key; value = newPair->value; return this; }
	pair<KT, VT>& operator=(const pair<KT, VT>* newPair) { key = newPair->key; value = newPair->value; return this; }*/
};

//template <typename KT, typename VT>
//pair<KT, VT>& pair<KT, VT>::operator=(pair<KT, VT>* other)
//{
//	
//	return *this;
//}

template <class KT, class VT>
pair<KT, VT>& pair<KT, VT>::operator=(const pair<KT, VT>& other)
{
	key = other.key;
	value = other.value;
	return *this;

	//if (this == nullptr)
	//{
	//	// Use the copy constructor
	//	*this = *(new pair<KT, VT>(other));

	//	//*this = *(new pair<KT, VT>());
	//}

	////this = pair();
	//if (this != &other)
	//{
	//	if (key != nullptr)
	//	{
	//		delete key;
	//	}

	//	if (value != nullptr)
	//	{
	//		delete value;
	//	}

	//	key = other.value == nullptr ? nullptr : new KT(*other.key);

	//	if (other.value == nullptr)
	//	{
	//		value = nullptr;
	//	}
	//	else
	//	{
	//		value = new VT(*other.value);
	//	}

	//	/*key = other.key;
	//	value = other.value;*/
	//}
	//return *this;
}


// Templated comparison function
template<typename KT>
using cmp = bool(*)(KT k1, KT k2);

template<class KT>
bool less(KT a, KT b)
{
	return a < b;
}

// Templated map class
template <class KT, class VT>
class map
{
private:
	cmp<KT> comp;
	int arrsize = 10;
	pair<KT, VT> * elements;
public:
	size_t numElements = 0;
	typedef mapit<KT, VT> iterator;
	typedef ptrdiff_t difference_type;
	typedef pair<KT, VT> value_type;;
	
	map();
	map(cmp<KT> comparator);
	~map();
	void insert(KT key, VT value);
	void shrinkToFit();
	VT lookup(KT key);
	VT linearlookup(KT key);
	VT binarylookup(KT key, int start, int end);
	VT& operator[](KT key)
	{
		return findOrInsert(key);
	}

	VT& findOrInsert(KT key)
	{
		// Run through looking for first key greater than the key
		for(int i = 0; i <= numElements; i++)
		{
			if (i == numElements)
			{
				elements[i] = *(new pair<KT, VT>(key));
				numElements++;
				return elements[i].value;
			}

			// If this elements is greater than the key
			if (!comp(elements[i].key, key))
			{
				// Check for equality
				if (!comp(key, elements[i].key))
				{
					// Return if equal
					return elements[i].value;
				}

				// Otherwise insert
				// Ensure there is space to insert
				checkSizeAndExpand();

				// Start by shuffling up all the remaining elements
				shuffleUp(i);

				// Insert a new element with nullptr as value and then return
				elements[i] = *(new pair<KT, VT>(key));
				numElements++;
				return elements[i].value;
			}
		}
	}

	void checkSizeAndExpand()
	{
		// If the array is full
		if (numElements == arrsize)
		{
			// Expand the array
			arrsize *= 2;
			//pair<KT, VT>* newArr[size];
			pair<KT, VT> * newArr = new pair<KT, VT>[arrsize];

			// Copy the contents and delete the old values
			for (int i = 0; i < arrsize / 2; i++)
			{
				newArr[i] = elements[i];
			}

			// Delete the old reference
			delete[] & elements[0];

			// Replace with new array reference
			elements = newArr;
		}
	}

	void shuffleUp(const int pivot)
	{
		// Shuffle up all elements from the current position by the given amount
		for (int j = numElements; j > pivot; j--)
		{
			elements[j] = elements[j - 1];
		}
	}

	const VT& operator[](const KT key)const
	{
		return lookup(key);
	}

	value_type& operator[](const size_t index)
	{
		return elements[index];
	}

	map<KT, VT>& operator=(VT value)
	{
		return *this;
	}

	size_t size() const {
		return numElements;
	}

	iterator begin()
	{
		return iterator(this, 0);
	}

	iterator end()
	{
		return iterator(this, size());
	}

	iterator lookupPair(KT key, const int first, const int last)
	{

		// Base case - reached an array of size 1
		// This could potentially by the correct key so we must check
		// If it is not we need to break out after the check
		bool lastPass = false;
		if ((last - first) <= 1)
		{
			lastPass = true;
		}

		// Recursive case
		// Find midpoint
		const int mid = first + (last - first) / 2;

		// Split the array and recurse down the correct half
		if (!comp(elements[mid].key, key))
		{
			// Equality check
			if (!comp(key, elements[mid].key))
			{
				// Return value
				return iterator(this, mid);
				//return elements[mid];
			}

			// Recurse left
			return lastPass == true ? end() : lookupPair(key, first, mid);
		}

		// Recurse right
		return lastPass == true ? end() : lookupPair(key, mid, last);
	}

	iterator find(KT key)
	{
		return lookupPair(key, 0, numElements);
	}
};

template<class KT, class VT>
map<KT, VT>::map()
{
	comp = less;

	// Initialise the arrya with the efault size of 10
	elements = new pair<KT, VT>[arrsize];
}

// Constructor
// Takes a function pointer parameter to a comparison function used to order and search the array
template<typename KT, typename VT>
map<KT, VT>::map(bool (*comparator)(KT, KT))
{
	comp = comparator;

	// Initialise the arrya with the efault size of 10
	elements = new pair<KT, VT>[arrsize];
}

template <class KT, class VT>
void map<KT, VT>::shrinkToFit()
{
	// Create the new array
	pair<KT, VT> * newArr = new pair<KT, VT>[numElements];

	// Copy the data
	for (int i = 0; i < numElements; i++)
	{
		newArr[i] = elements[i];
	}
	
	// Delete old memory objects
	delete[] & elements[0];

	// Replace with new array reference
	elements = newArr;
}

// Template destructor
template<typename KT, typename VT>
map<KT, VT>::~map()
{
	// Calls the destructor for every element
	// Deallocates the memory for the structure itself
	delete[] elements;
}

// Ordered map.
// Would have to use shuffle up regardless of implementation on deletions to maximise space
// Would have O(n) insert for non-ordered
// Still have O(n) insert with ordered map
// Could use a binary search to "lookup" the position of the value to insert
// This would give a O(n + logn) = O(n)
// Worse worst case, better average cases for large data sets
// Allows for O(logn) lookup)
template<typename KT, typename VT>
void map<KT, VT>::insert(KT key, VT value)
{
	// Expand the array if it is full
	checkSizeAndExpand();

	// If this is the first element, just insert it
	if (numElements == 0)
	{
		elements[0] = *(new pair<KT, VT>(key, value));
		numElements++;
		return;
	}

	// Iterate until we find the position for the key
	for (int i = 0; i <= numElements; i++)
	{
		if (i == numElements)
		{
			// Then insert as we are at the end
			elements[i] = *(new pair<KT, VT>(key, value));
			break;
		}

		if (!comp(elements[i].key, key))
		{
			// Then insert the key
			if (i + 1 <= numElements)
			{
				// Then shuffle up the remaining elements
				shuffleUp(i);
			}
			
			// Then insert
			elements[i] = *(new pair<KT, VT>(key, value));
			break;
		}

	}

	numElements++;
}

//template<typename KT, typename VT, typename CT>
//mapit<KT,VT,CT> map<KT,VT,CT>::lookup(KT key)
//{
//	
//}

// TODO change to binary search
template<typename KT, typename VT>
VT map<KT, VT>::linearlookup(KT key)
{
	for (int i = 0; i < numElements; i++)
	{
		// If key is not less than the current one
		if (!comp(*elements[i].key, key))
		{
			// Then check if it is not greater than it (equal to)
			if (!comp(key, *elements[i].key))
			{
				// Return the corresponding value
				return *elements[i].value;
			}

			// Otherwise stop looking 
			break;
		}
	}

	return 0;
}

template<typename KT, typename VT>
VT map<KT, VT>::lookup(KT key)
{
	return binarylookup(key, 0, numElements);
}

template<typename KT, typename VT>
VT map<KT, VT>::binarylookup(KT key, const int start, const int end)
{
	// Base case - reached an array of size 1
	// This could potentially by the correct key so we must check
	// If it is not we need to break out after the check
	bool last = false;
	if ((end - start) <= 1)
	{
		last = true;
	}

	// Recursive case
	// Find midpoint
	int mid = start + (end - start) / 2;

	// Split the array and recurse down the correct half
	if (!comp(elements[mid].key, key))
	{
		// Equality check
		if (!comp(key, elements[mid].key))
		{
			// Return value
			return elements[mid].value;
		}

		// Recurse left
		return last == true ? 0 : binarylookup(key, start, mid);
	}

	// Recurse right
	return last == true ? 0 : binarylookup(key, mid, end);
}

