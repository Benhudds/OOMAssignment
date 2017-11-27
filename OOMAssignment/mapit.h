#pragma once

// Forward declaration of pair
template <class KT, class VT>
class pair;

// Forward declaration of map
template <class KT, class VT>
class map;

// Template map iterator
// Bidirectional
template <class KT, class VT>
class mapit
{
	// Type declarations
public:
	// Self type
	typedef mapit<KT, VT> self_type;

	// Environment specific size type
	typedef size_t size_type;

	// Value type of iterator
	typedef pair<KT, VT> value_type;

	// Map type
	typedef map<KT, VT> maptype;
	
	// Make map a friend of this class so that it can access private members (pos)
	friend map <KT, VT>;

	// Private members
private:
	// Reference to the map
	maptype *map;

	// Position within the map
	size_type pos;

	// Constructors
public:
	mapit(maptype *pmap, const size_type n)
	{
		map = pmap;
		pos = n;
	}

	// Operators
public:
	// Prefix increment operator
	self_type& operator++()
	{
		++pos;
		return *this;
	}

	// Postfix increment operator
	self_type operator++(int)
	{
		self_type temp(*this);
		++(*this);
		return temp;
	}

	// Prefix decrement operator
	self_type& operator--()
	{
		--pos;
		return *this;
	}

	// Postfix decrement operator
	self_type operator--(int)
	{
		self_type temp(*this);
		--(*this);
		return temp;
	}

	// Addition operator
	self_type operator+(const size_type n)
	{
		self_type tmp(*this);
		tmp.pos += n;
		return tmp;
	}

	// Addition Assignment operator
	self_type &operator+=(const size_type n) {
		pos += n;
		return *this;
	}

	// Subtraction operator
	self_type operator-(const size_type n)
	{
		self_type tmp(*this);
		tmp.pos -= n;
		return tmp;
	}

	// Subtraction Assignment operator
	self_type &operator-=(const size_type n) {
		pos -= n;
		return *this;
	}

	// Equality operator
	bool operator==(self_type n)
	{
		return (pos == n.pos);
	}

	// Inequality operator
	bool operator!=(const self_type n)
	{
		return !this->operator==(n);
	}

	// Dereference operator
	value_type &operator*()
	{
		return (*map)[pos];
	}

	// Arrow operaetor
	value_type *operator->()
	{
		return &(operator*());
	}
};

