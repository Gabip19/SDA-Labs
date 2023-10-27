#pragma once
#include "IteratorColectie.h"

typedef int TElem;

typedef struct
{
	TElem el;
	int frecv;
} TElemCol;

typedef bool(*Relatie)(TElem, TElem);


// in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);


class IteratorColectie;


class Colectie
{

	friend class IteratorColectie;

private:

	int cp;				// capacitate memorare vectori
	TElemCol* elem;		// lista cu elementele din colectie
	int* urm;			// lista cu pozitiile elementelor urmatoare
	int prim;			// primul element din colectie
	int primLiber;		// pozitia primului element liber
	int len;			// numarul elementelor din colectie
	
	int aloca();
	void dealoca(int i);
	int creeazaNod(TElem el);
	void redim();

public:

	// constructorul implicit
	Colectie();

	// adauga un element in colectie
	void adauga(TElem e);

	// sterge o aparitie a unui element din colectie
	// returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	// elimina nr aparitii ale elementului elem. In cazul in care elementul apare mai putin de nr ori, toate aparitiile sale vor fi eliminate.
	// returneaza numarul de aparitii eliminate ale elementului.
	// arunca exceptie in cazul in care este nr este negativ.
	int eliminaAparitii(int nr, TElem el);

	// verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	// returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;

	// intoarce numarul de elemente din colectie
	int dim() const;

	// verifica daca colectia e vida
	bool vida() const;

	//// adauga aparitii multiple ale unui element
	//// arunca exceptie in cazul în care este nr este negativ
	//void adaugaAparitiiMultiple(int nr, TElem elem);

	// returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

};