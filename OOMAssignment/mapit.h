#pragma once
#include "map.h"

template <class KT, class VT>
class pair;

template <class KT, class VT>
class map;

// Templated iterator
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
private:
	maptype *map;
	size_type pos;
};

