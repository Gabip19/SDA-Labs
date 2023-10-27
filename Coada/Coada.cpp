
#include "Coada.h"
#include <exception>
#include <iostream>

using namespace std;


Coada::Coada() 
{
	this->cp = 3;
	this->fata = 0;
	this->spate = 0;
	this->elems = new TElem[this->cp];
}


void Coada::adauga(TElem elem) 
{
	if ((fata == 0 && spate == cp - 1) || (fata == spate + 1))
		redim();

	elems[spate] = elem;

	if (spate == cp - 1)
		spate = 0;
	else
		spate++;
}


TElem Coada::element() const
{
	if (vida())
		throw std::runtime_error("Coada este vida");

	TElem e = elems[fata];
	return e;
}


TElem Coada::sterge() 
{
	TElem e = element();
	if (fata == cp - 1)
		fata = 0;
	else
		fata++;
	return e;
}


bool Coada::vida() const 
{
	return fata == spate;
}


Coada::~Coada()
{
	delete[] this->elems;
}


void Coada::redim()
{
	TElem* new_elems = new TElem[cp * 2];
	int k = 0;

	if (fata < spate)
	{
		for (int i = fata; i < spate; ++i)
		{
			new_elems[k++] = elems[i];
		}
	}
	else if (fata > spate)
	{
		for (int i = fata; i < cp; ++i)
		{
			new_elems[k++] = elems[i];
		}
		for (int i = 0; i < spate; ++i)
		{
			new_elems[k++] = elems[i];
		}
	}

	cp = 2 * cp;
	fata = 0;
	spate = k;

	delete[] elems;

	elems = new_elems;
}