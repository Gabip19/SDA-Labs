#include <iostream>

#include "TestExtins.h"
#include "TestScurt.h"

#include "Colectie.h"
#include <assert.h>
#include <exception>

using namespace std;


void testNou()
{
	Colectie a;
	a.adaugaAparitiiMultiple(2, 3);
	assert(a.cauta(3) == true);
	
	a.adaugaAparitiiMultiple(5, 5);
	assert(a.cauta(5) == true);
	
	a.adaugaAparitiiMultiple(5, 3);
	assert(a.nrAparitii(5) == 5);
	assert(a.nrAparitii(3) == 7);
	
	a.adaugaAparitiiMultiple(2, 4);
	assert(a.cauta(4) == true);
	assert(a.nrAparitii(4) == 2);

	a.adaugaAparitiiMultiple(4, 7);
	assert(a.cauta(7) == true);
	assert(a.nrAparitii(7) == 4);

	assert(a.dim() == 18);

	try
	{
		a.adaugaAparitiiMultiple(-3, 4);
		assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}

	try
	{
		a.adaugaAparitiiMultiple(0, 4);
		assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}
}


int main()
{
	testNou();
	testAllExtins();
	testAll();
}
