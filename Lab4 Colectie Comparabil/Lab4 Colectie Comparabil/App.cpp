#include <iostream>

#include "Colectie.h"
#include "TestScurt.h"
#include "TestExtins.h"
#include <assert.h>
#include <exception>

using namespace std;


void testNou()
{
	Colectie a;
	a.adauga(1);
	a.adauga(1);
	a.adauga(5);
	a.adauga(3);
	a.adauga(7);
	a.adauga(8);
	a.adauga(9);
	a.adauga(10);
	a.adauga(11);
	a.adauga(10);
	a.adauga(12);
	
	assert(a.dim() == 11);

	assert(a.eliminaAparitii(3, 1) == 2);
	assert(a.eliminaAparitii(5, 1) == 0);
	assert(a.eliminaAparitii(1, 12) == 1);
	
	try
	{
		a.eliminaAparitii(-3, 1);
		assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}

	assert(a.dim() == 8);

	a.adauga(-20);
	a.adauga(-20);
	a.adauga(-20);
	a.adauga(-20);
	a.adauga(-20);
	a.adauga(-19);
	a.adauga(-19);
	a.adauga(-19);

	assert(a.eliminaAparitii(5, -20) == 5);
	assert(a.eliminaAparitii(2, -19) == 2);
	assert(a.nrAparitii(-19) == 1);

	a.sterge(11);
	assert(a.cauta(11) == false);

	IteratorColectie it2 = a.iterator();
	while (it2.valid())
	{
		//cout << it2.element() << " ";
		it2.urmator();
	}

	//assert(a.cauta(3) == true);

	//assert(a.cauta(5) == true);

	//assert(a.nrAparitii(5) == 1);
	//assert(a.nrAparitii(1) == 2);

	//assert(a.cauta(4) == false);
	//assert(a.nrAparitii(10) == 2);

	//assert(a.cauta(7) == true);
	//assert(a.nrAparitii(7) == 1);
}


int main()
{
	testNou();
	testAll();
	testAllExtins();
}