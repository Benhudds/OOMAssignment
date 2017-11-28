// OOMAssignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include "map.h"

bool compfunc(char a, char b)
{
	throw UserComparisonFunctionException();
}

struct cmprev
{
	bool operator()(const char *a, const char *b) const
	{
		return &b < &a;
	}
};

int main()
{
	// Initialise comparison
	std::map<char, int> stdmap;
	map<char, int> adtmap;

	std::cout << "stdmap initial size = " << stdmap.size() << std::endl;
	std::cout << "adtmap initial size = " << adtmap.size() << std::endl;

	std::cout << std::endl;

	// Insert value
	std::cout << "stdmap - inserting value 1 for key a" << std::endl;
	stdmap.insert_or_assign('a', 1);

	std::cout << "adtmap - inserting value 1 for key a" << std::endl;
	adtmap.insert('a', 1);

	std::cout << std::endl;

	// Check inserted value
	std::cout << "stdmap - key a has value " << stdmap['a'] << std::endl;
	std::cout << "adtmap - key a has value " << adtmap['a'] << std::endl;

	std::cout << std::endl;

	// Check size after inserted value
	std::cout << "stdmap new size = " << stdmap.size() << std::endl;
	std::cout << "adtmap new size = " << adtmap.size() << std::endl;

	std::cout << std::endl;

	// Erase inserted item by key
	std::cout << std::endl << "Erase inserted item by key" << std::endl;
	std::cout << "stdmap - removing element for key a" << std::endl;
	int removed = stdmap.erase('a');
	std::cout << "stdmap - " << removed << " elements were removed" << std::endl;

	std::cout << std::endl;

	std::cout << "adtmap - removing element for key a" << std::endl;
	removed = adtmap.erase('a');
	std::cout << "adtmap - " << removed << " elements were removed" << std::endl;

	std::cout << std::endl;

	// Check size after erase
	std::cout << "stdmap new size = " << stdmap.size() << std::endl;
	std::cout << "adtmap new size = " << adtmap.size() << std::endl;

	std::cout << std::endl;

	// Get iterator to item by key
	std::cout << std::endl << "Find inserted item" << std::endl;
	stdmap.insert_or_assign('a', 1);
	adtmap.insert('a', 1);

	auto stdit = stdmap.find('a');
	std::cout << "stdmap find returned iterator for parameter 'a' with key " << stdit->first << " and value " << stdit->second << std::endl;
	auto adtit = adtmap.find('a');
	std::cout << "adtmap find returned iterator for parameter 'a' with key " << adtit->first << " and value " << adtit->second << std::endl;

	std::cout << std::endl;

	// Erase inserted item by iterator
	std::cout << std::endl << "Erase inserted item by iterator (a, 1)" << std::endl;

	stdmap.insert_or_assign('b', 2);
	std::cout << "stdmap - size before erase " << stdmap.size() << std::endl;
	stdit = stdmap.erase(stdit);
	std::cout << "stdmap - size after erase " << stdmap.size() << std::endl;
	std::cout << "stdmap returned iterator after erase with key " << stdit->first << " and value " << stdit->second << std::endl;
	
	std::cout << std::endl;

	adtmap.insert('b', 2);
	std::cout << "adpmap - size before erase " << adtmap.size() << std::endl;
	adtit = adtmap.erase(adtit);
	std::cout << "adtmap - size after erase " << adtmap.size() << std::endl;
	std::cout << "adtmap returned iterator after erase with key " << adtit->first << " and value " << adtit->second << std::endl;
	
	// Using the [] operator
	std::cout << std::endl << "Using the [] operator" << std::endl;

	stdmap['a'] = 1;
	std::cout << "stdmap - key a has value " << stdmap['a'] << std::endl;

	adtmap['a'] = 1;
	std::cout << "adtmap - key a has value " << stdmap['a'] << std::endl;
	
	// Clearing the map
	std::cout << std::endl << "Clearing the map" << std::endl;

	std::cout << "stdmap - size = " << stdmap.size() << std::endl;
	stdmap.clear();
	std::cout << "stdmap - size = " << stdmap.size() << std::endl;

	std::cout << "adtmap - size = " << adtmap.size() << std::endl;
	adtmap.clear();
	std::cout << "adtmap - size = " << adtmap.size() << std::endl;









	// Addition of items beyond the bounds of the initial array
	std::cout << std::endl << "Addition of items beyond the bounds of the initial array" << std::endl;
	
	std::cout << std::endl << "Initial adtmap array size = " << adtmap.arraysize() << std::endl;

	for(int i = 0; i < 11; i++)
	{
		adtmap[char(97 + i)] = i;
	}

	std::cout << "Number of elements in adtmap = " << adtmap.size() << std::endl;
	std::cout << "Post addition of items adtmap array size = " << adtmap.arraysize() << std::endl;

	// Validity of data inserted
	std::cout << std::endl << "Validity of data inserted" << std::endl;

	for(int i = 0; i < 11 ; i++)
	{
		std::cout << adtmap[char(97 + i)] << ", ";
	}

	std::cout << std::endl;

	// Use of iterator
	std::cout << std::endl << "Use of iterator" << std::endl;

	for(auto it = adtmap.begin(); it != adtmap.end(); it++)
	{
		std::cout << "key = " << it->first << " and value = " << it->second << std::endl;
	}

	std::cout << "reverse" << std::endl;

	for(auto it = adtmap.rend(); it != adtmap.rbegin(); it--)
	{
		std::cout << "key = " << it->first << " and value = " << it->second << std::endl;
	}

	// Attempting to erase an element out of range
	std::cout << std::endl << "Attempting to erase an element out of range in the collection" << std::endl;

	const auto outOfRange = adtmap.end();
	
	try
	{
		adtmap.erase(outOfRange);

		std::cout << "Exception not thrown" << std::endl;
	}
	catch (MapException e)
	{
		std::cout << "Exception was thrown " << std::endl;
	}
	
	// Clearing and shrinking the map
	std::cout << std::endl << "Clearing and shrinking the map" << std::endl;

	std::cout << "adtmap arraysize before clear = " << adtmap.arraysize() << std::endl;
	adtmap.clear();
	std::cout << "adtmap arraysize after clear = " << adtmap.arraysize() << std::endl;
	adtmap.shrinkToFit();
	std::cout << "adtmap arraysize after shrink = " << adtmap.arraysize() << std::endl;

	// Throw an exception in a user defined function
	std::cout << std::endl << "Throwing an exception in a user defined comparison function" << std::endl;
	adtmap = * new map<char, int>(compfunc);

	try
	{
		adtmap['a'] = 0;

		std::cout << "Exception not thrown" << std::endl;
	}
	catch (MapException e)
	{
		std::cout << "Exception was thrown " << std::endl;
	}


	system("pause");
	return 0;
}

