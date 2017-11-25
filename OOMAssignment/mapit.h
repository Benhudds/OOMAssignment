#pragma once
#include "map.h"

// Forward declaration of pair
template <class KT, class VT>
class pair;

// Forward declaration of map
template <class KT, class VT>
class map;

// Template map iterator
template <class KT, class VT>
class mapit
{
public:
	typedef mapit<KT, VT> self_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef pair<KT, VT> value_type;
	typedef pair<KT, VT>* Pointer;
	typedef map<KT, VT> maptype;
	
	// Constructor
	mapit(maptype *pmap, size_type n)
	{
		map = pmap;
		pos = n;
	}

	self_type& operator++()
	{
		++pos;
		return *this;
	}

	self_type operator++(int)
	{
		self_type temp(*this);
		++(*this);
		return temp;
	}

	self_type& operator--()
	{
		--pos;
		return *this;
	}

	self_type operator--(int)
	{
		self_type temp(*this);
		--(*this);
		return temp;
	}

	self_type operator+(difference_type n)
	{
		self_type tmp(*this);
		tmp.pos += n;
		return tmp;
	}
	self_type &operator+=(difference_type n) {
		pos += n;
		return *this;
	}

	self_type operator-(difference_type n)
	{
		self_type tmp(*this);
		tmp.pos -= n;
		return tmp;
	}
	self_type &operator-=(difference_type n) {
		pos -= n;
		return *this;
	}

	bool operator==(self_type n)
	{
		return (pos == n.pos);
	//	return (&this == &n);
	}

	bool operator!=(self_type n)
	{
		return !this->operator==(n);
		//return !(this == n);
	}

	value_type &operator*()
	{
		return (*map)[pos];
	}

	value_type *operator->()
	{
		return &(operator*());
	}

	// Make map a friend of this class so that it can access private members (pos)
	friend map <KT, VT>;

private:
	// Reference to the map
	maptype *map;

	// Position within the map
	size_type pos;
};

