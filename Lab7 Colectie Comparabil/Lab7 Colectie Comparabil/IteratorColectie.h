#pragma once
#include "Colectie.h"
#include <stack>
using std::stack;


class Colectie;
class Nod;

typedef int TElem;
typedef Nod* PNod;


class IteratorColectie
{
	
	friend class Colectie;

private:

    // contine o referinta catre containerul pe care il itereaza
	const Colectie& col;
	
	/* aici e reprezentarea specifica a iteratorului */
	PNod curent;			// nodul curent spre care indica
	int aparitie;			// nr aparitiei elementului spre care indidca
	stack<PNod> stiva;		// stiva pe care se vor pune elementele pt parcurgerea in INORDINE
	
	// constructorul primeste o referinta catre Container
	// iteratorul va referi primul element din container
	IteratorColectie(const Colectie& c);

public:

	// reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	// muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	// verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	// returneaza valoarea elementului din container referit de iterator
	// arunca exceptie daca iteratorul nu e valid
	TElem element() const;

};