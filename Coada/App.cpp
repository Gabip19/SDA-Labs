#include <crtdbg.h>
#include <iostream>
#include <assert.h>
#include "Coada.h"
#include "TestExtins.h"
#include "TestScurt.h"
using namespace std;


void f()
{
	Coada a, b, c;
	cout << a.vida() << "\n";
	try
	{
		a.element();
		assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}
	a.adauga(3);
	cout << a.element() << "\n";
	a.adauga(4);
	a.adauga(5);
	a.sterge();
	cout << a.element() << "\n";
	a.adauga(12);
	a.adauga(10);
	a.sterge();
	a.sterge();
	a.adauga(6);
	a.adauga(7);
	cout << a.element() << "\n";
	a.sterge();
	cout << a.element() << "\n";
	a.sterge();
	a.adauga(13);
	a.adauga(14);
	a.adauga(15);
	a.adauga(16);
	a.adauga(17);
	a.sterge();
	a.sterge();
	a.sterge();
	a.sterge();
	a.sterge();
	a.sterge();
	cout << a.element() << "\n";
	a.sterge();
	try
	{
		a.sterge();
		assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}
	cout << a.vida() << "\n";
}


int main() {
	testAll();
	testAllExtins();
	//f();
	//_CrtDumpMemoryLeaks();
	return 0;
}
