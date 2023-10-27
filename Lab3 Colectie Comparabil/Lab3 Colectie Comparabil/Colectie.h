#pragma once;
#include "IteratorColectie.h"

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);


// in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);


class IteratorColectie;
class Nod;

typedef Nod* PNod;


// clasa Nod responsabila pentru reprezentarea LSI-ului
class Nod
{

private:

	TElem el;	// elementul din nodul respectiv
	int frecv;	// numarul de aparitii al elementului in colectie
	PNod urm;	// pointer catre urmatorul nod din colectie

public:

	friend class Colectie;

	// constructor
	Nod(TElem e, PNod urm);

	// returneaza elementul din nodul curent
	TElem element();
	
	// returneaza numarul de aparitii a elementului din nodul curent in colectie
	int frecventa();

	// returneaza pointerul catre urmatorul nod din colectie
	PNod urmator();

};



class Colectie 
{
	
	friend class IteratorColectie;

private:

	PNod prim;	// nodul de start din cadrul LSI-ului
	int len;	// numarul elementelor din colectie

public:
		
	// constructorul implicit
	Colectie();

	// adauga un element in colectie
	void adauga(TElem e);

	// sterge o aparitie a unui element din colectie
	// returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	// verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	// returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;

	// intoarce numarul de elemente din colectie
	int dim() const;

	// verifica daca colectia e vida
	bool vida() const;

	// adauga aparitii multiple ale unui element
	// arunca exceptie in cazul în care este nr este negativ
	void adaugaAparitiiMultiple(int nr, TElem elem);

	// returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

};