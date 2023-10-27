#include <iostream>
#include <crtdbg.h>
#include <assert.h>
#include "Colectie.h"
#include "TestScurt.h"
#include "TestExtins.h"

using namespace std;


void test_fct()
{
	Colectie c;
	c.adauga(15);
	c.adauga(0);
	c.adauga(0);
	c.adauga(10);
	c.adauga(110);
	c.adauga(20);
	c.adauga(50);
	c.adauga(12);

	assert(c.dim() == 8);
	assert(c.cauta(15) == true);
	assert(c.cauta(12) == true);
	assert(c.cauta(110) == true);
	assert(c.cauta(0) == true);
	assert(c.cauta(111) == false);
	assert(c.cauta(-3) == false);
	assert(c.cauta(60) == false);

	c.adauga(110);
	c.adauga(110);
	c.adauga(12);

	assert(c.nrAparitii(0) == 2);
	assert(c.nrAparitii(110) == 3);
	assert(c.nrAparitii(12) == 2);
	assert(c.nrAparitii(50) == 1);
	assert(c.nrAparitii(15) == 1);
	assert(c.nrAparitii(60) == 0);
	assert(c.nrAparitii(111) == 0);
	
	assert(c.sterge(111) == false);
	assert(c.sterge(60) == false);
	assert(c.dim() == 11);
	
	assert(c.sterge(110) == true);
	assert(c.nrAparitii(110) == 2);
	assert(c.dim() == 10);
	
	assert(c.sterge(110) == true);
	assert(c.nrAparitii(110) == 1);
	assert(c.dim() == 9);

	assert(c.sterge(110) == true);
	assert(c.nrAparitii(110) == 0);
	assert(c.dim() == 8);

	assert(c.sterge(110) == false);
	assert(c.dim() == 8);

	assert(c.sterge(20) == true);
	assert(c.nrAparitii(20) == 0);
	assert(c.dim() == 7);

	auto it = c.iterator();
	while (it.valid())
	{
		//cout << it.element() << " ";
		it.urmator();
	}
	assert(it.valid() == false);

	c.adaugaAparitiiMultiple(10, 1000);
	assert(c.nrAparitii(1000) == 10);

	c.adaugaAparitiiMultiple(5, 1000);
	assert(c.nrAparitii(1000) == 15);

	c.adaugaAparitiiMultiple(20, 1111);
	assert(c.nrAparitii(1111) == 20);

	try
	{
		c.adaugaAparitiiMultiple(-3, 20);
		assert(false);
	}
	catch (const std::exception&)
	{
		assert(true);
	}

	try
	{
		c.adaugaAparitiiMultiple(0, 31);
		assert(false);
	}
	catch (const std::exception&)
	{
		assert(true);
	}

	c.adaugaAparitiiMultiple(10, 15);
	assert(c.nrAparitii(15) == 11);
}


int main()
{
	test_fct();
	testAll();
	testAllExtins();
	_CrtDumpMemoryLeaks();
	cout << "DONE\n";
	return 0;
}