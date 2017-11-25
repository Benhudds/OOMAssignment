// OOMAssignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include "map.h"

typedef bool cmpp(char a, char b);

bool compfunc(char* a, char* b)
{
	return &a < &b;
}

bool compfunc(char a, char b)
{
	return a < b;
}

bool compfuncint(int a, int b)
{
	return a < b;
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
	std::cout << "adtmap find returned iterator for parameter 'a' with key " << adtit->key << " and value " << adtit->value << std::endl;

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
	std::cout << "adtmap returned iterator after erase with key " << adtit->key << " and value " << adtit->value << std::endl;
	
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

	std::cout << "Post addition of items adtmap array size = " << adtmap.arraysize() << std::endl;

	// Validity of data inserted
	std::cout << std::endl << "Validity of data inserted" << std::endl;

	for(int i = 0; i < 11 ; i++)
	{
		std::cout << adtmap[char(97 + i)] << std::endl;
	}

	





	std::map<char, int> stlmap;
	std::map<char, int>::iterator stlit;

	map<char, int> testmap;
	testmap['a'] = 1;
	auto b = testmap.begin();
	testmap['b'] = 2;
	testmap['k'] = 11;
	testmap['j'] = 10;
	testmap['c'] = 3;
	testmap['h'] = 8;
	testmap['e'] = 5;
	testmap['d'] = 4;
	testmap['g'] = 7;
	testmap['f'] = 6;
	testmap['i'] = 9;
	testmap['i'] = 99;

	auto end = testmap.end();

	for(auto it = testmap.begin(); it != testmap.end(); it++)
	{
		std::cout << it->key << std::endl;
		
	}


	stlmap.size();

	/*map<int, char> * myintmap = new map<int, char>(compfuncint);
	myintmap->insert(0, 'a');*/

	

	stlmap['a'] = 50;
	stlmap['c'] = 150;
	stlmap['b'] = 100;
	stlmap['d'] = 200;

	stlit = stlmap.find('b');
	if (stlit != stlmap.end())
		stlmap.erase(stlit);

	for(auto it = stlmap.begin(); it != stlmap.end(); it++)
	{
		std::cout << it->second << std::endl;
	}

	auto it = stlmap.find('a');
	auto ita = testmap.find('a');
	std::cout << "&&" << it->first << std::endl;
	std::cout << "**" << ita->key << std::endl;

	ita->key;

	// print content:
	std::cout << "elements in stlmap:" << '\n';
	std::cout << "a => " << stlmap.find('a')->second << '\n';
	std::cout << "c => " << stlmap.find('c')->second << '\n';
	std::cout << "d => " << stlmap.find('d')->second << '\n';


	system("pause");
	return 0;
}

