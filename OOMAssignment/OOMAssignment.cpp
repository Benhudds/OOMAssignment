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
	std::map<char, int, cmprev> tmap;
	
	std::map<char, int> stlmap;
	std::map<char, int>::iterator stlit;
	map<char, int>* mymap = new map<char, int>(compfunc);

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

	mymap->insert('b', 2);
	mymap->insert('c', 3);
	mymap->insert('d', 4);
	mymap->insert('a', 1);
	mymap->insert('e', 5);
	mymap->insert('f', 6);
	mymap->insert('g', 7);
	mymap->insert('h', 8);
	mymap->insert('i', 9);
	mymap->insert('j', 10);
	mymap->insert('k', 11);
	
	auto stltest = stlmap['e'];
	auto test = (*mymap)['a'];
	mymap['a'] = 100;

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

	std::cout << "elements in mymap:" << std::endl;
	std::cout << "a => " << mymap->lookup('a') << std::endl;
	std::cout << "b => " << mymap->lookup('b') << std::endl;
	std::cout << "c => " << mymap->lookup('c') << std::endl;
	std::cout << "d => " << mymap->lookup('d') << std::endl;
	std::cout << "e => " << mymap->lookup('e') << std::endl;
	std::cout << "f => " << mymap->lookup('f') << std::endl;
	std::cout << "g => " << mymap->lookup('g') << std::endl;
	std::cout << "h => " << mymap->lookup('h') << std::endl;
	std::cout << "i => " << mymap->lookup('i') << std::endl;
	std::cout << "j => " << mymap->lookup('j') << std::endl;
	std::cout << "k => " << mymap->lookup('k') << std::endl;
	std::cout << "l => " << mymap->lookup('l') << std::endl;

	system("pause");
	return 0;
}

