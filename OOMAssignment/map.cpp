#include "stdafx.h"

template<typename KT>
struct CT
{
	bool operator()(const KT k1, const KT k2);
};

template<typename KT, typename VT>
class pair
{
private:
public:
	KT* key;
	VT* value;

	//pair(KT const & newKey, VT const & newValue) : key(newKey), value(newValue) {}
	pair(KT newKey, VT newValue)
	{
		key = new KT(newKey);
		//key = new KT;
		//key = &newKey;

		value = new VT(newValue);
		/*value = new VT;
		value = &newValue;*/
	}

	pair(const pair &obj)
	{
		key = new KT;
		*key = *obj.key;

		value = new VT;
		*value = *obj.value;
	}

	pair()
	{
		//key = new KT;
		key = nullptr;

		//value = new VT;
		value = nullptr;
	}

	//CTwoInts CTwoInts::operator = ( CTwoInts operand )
	//pair<KT, VT> operator=(pair<KT, VT> newPair) { key = newPair->key, value = newPair->value; return *this; }
	/*pair<KT, VT> operator=(pair<KT, VT>* newPair)
	{
	key = newPair->key;
	value = newPair->value;
	return *this;
	}*/

	pair<KT, VT>& operator=(pair<KT, VT>* other);
	pair<KT, VT>& operator=(const pair<KT, VT>& other);

	/*pair<KT, VT>& operator=(const pair<KT, VT> newPair) { key = newPair->key; value = newPair->value; return this; }
	pair<KT, VT>& operator=(const pair<KT, VT>* newPair) { key = newPair->key; value = newPair->value; return this; }*/
};

template <typename KT, typename VT>
pair<KT, VT>& pair<KT, VT>::operator=(pair<KT, VT>* other)
{

	return *this;
}

template <class KT, class VT>
pair<KT, VT>& pair<KT, VT>::operator=(const pair<KT, VT>& other)
{
	if (this == nullptr)
	{
		*this = *(new pair<KT, VT>());
	}

	//this = pair();
	if (this != &other)
	{
		delete key;
		delete value;
		key = other.key;
		value = other.value;
	}
	return *this;
}

template <class KT, class VT>
class mapit
{
public:
	mapit(pair<KT, VT>* ptr = nullptr);
};

template<typename KT>
using cmp = bool(*)(KT k1, KT k2);
template <class KT, class VT>
class map
{
private:
	cmp<KT> comp;
	static const int defsize = 10;
	int arrsize = 10;
	pair<KT, VT> * elements[defsize];
public:
	int numElements = 0;
	typedef mapit<KT, VT> iterator;
	iterator begin();
	map(cmp<KT> comparator);
	~map();
	void insert(KT key, VT value);
	VT lookup(KT key);
};

template<typename KT, typename VT>
map<KT, VT>::map(bool(*comparator)(KT, KT))
{
	comp = comparator;

	//elements = new pair<KT, VT>[size];

	//elements = new pair<KT, VT>[size];
	/*for (int i = 0; i < size ; i++)
	{
	elements[i] = *(new pair<KT, VT>());
	}*/
	//elements = new pair<KT, VT>*[size];
}

template<typename KT, typename VT>
map<KT, VT>::~map()
{
	for (int i = 0; i < arrsize; i++)
	{
		delete elements[i];
	}
	delete elements;
}

template<typename KT, typename VT>
void map<KT, VT>::insert(KT key, VT value)
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
			newArr[i] = *elements[i];
			delete elements[i];
		}

		// Delete the old reference
		//delete elements;

		// Replace with new array reference
		*elements = newArr;
	}

	// If this is the first element, just insert it
	if (numElements == 0)
	{
		elements[0] = new pair<KT, VT>(key, value);
		numElements++;
		return;
	}

	// Iterate until we find the position for the key
	for (int i = 0; i <= numElements; i++)
	{
		if (i == numElements)
		{
			// Then insert as we are at the end
			elements[i] = new pair<KT, VT>(key, value);
			break;
		}

		if (!comp(*elements[i]->key, key))
		{
			// Then insert the key
			if (i + 1 == numElements)
			{
				// Then shuffle up the remaining elements
				for (int j = numElements; j > i; j--)
				{
					elements[j] = elements[j - 1];
				}
			}

			// Then insert
			elements[i] = new pair<KT, VT>(key, value);
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
VT map<KT, VT>::lookup(KT key)
{
	for (int i = 0; i < numElements; i++)
	{
		// If key is not less than the current one
		if (!comp(key, *elements[i]->key))
		{
			// Then check if it is not greater than it (equal to)
			if (comp(*elements[i]->key, key))
			{
				// Return the corresponding value
				return *elements[i]->value;
			}

			// Otherwise stop looking 
			break;
		}
	}

	return 0;
}