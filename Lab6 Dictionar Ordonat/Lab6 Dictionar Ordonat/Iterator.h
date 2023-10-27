#pragma once

#include "DO.h"
#include <vector>

using std::vector;


class Iterator
{
	
	friend class DO;

private:
	
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	Iterator(const DO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const DO& dict;

	/* aici e reprezentarea specifica a iteratorului */
	vector<TElem> do_pairs;		// vectorul perechilor nenule din dictionar
	int curent;					// index la perechea curenta

public:

	// reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	// muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element() const;

};