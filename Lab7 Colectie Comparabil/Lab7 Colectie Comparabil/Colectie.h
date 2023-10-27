#pragma once
#include "IteratorColectie.h"

typedef int TElem;

struct TElemCol
{
	// Tipul elementelor din colectie
	// ce contine un element si frecventa sa
	TElem val;
	int frec = 0;
};


typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);


class Colectie;
class IteratorColectie;
class Nod;


typedef Nod* PNod;

class Nod
{
	// Clasa pentru reprezentarea nodurilor
	friend class Colectie;
	friend class IteratorColectie;
private:
	TElemCol el;		// elementul din nod
	PNod st;			// radacina subarborelui stang
	PNod dr;			// radacina subarborelui drept
	PNod parinte;		// adresa nodului parinte
public:
	Nod(TElem el, PNod st, PNod dr);
};


class Colectie
{

	friend class IteratorColectie;

private:
	
	PNod rad;		// radacina arborelui
	int nr;			// nr de elemente din colectie

	// fct utilitara pt adaugarea recursiva
	PNod adauga_rec(PNod p, TElem e);

	PNod adauga_rec_multiple(PNod p, TElem e, int nr);


	// fct utilitara pt stergerea recursiva
	PNod sterge_rec(PNod p, TElem e, bool& sters);
	
	// fct utilitara pt determinarea minimului dintr-un arbore
	PNod minim(PNod p);

	// fct utilitara pt distrugerea recursiva a arborelui
	void distruge_rec(PNod p);

public:
		
	// constructorul implicit
	Colectie();

	// adauga un element in colectie
	void adauga(TElem e);

	// adauga nr aparitii ale elementului elem in colectie.
	// arunca exceptie in cazul in care este nr este negativ.
	void adaugaAparitiiMultiple(int nr, TElem elem);

	// sterge o aparitie a unui element din colectie
	// returneaza adevarat daca s-a putut sterge
	/// varianta recursiva (STACK OVERFLOW pt date foarte mari)
	bool sterge_r(TElem e);

	// sterge o aparitie a unui element din colectie
	// returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	// verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	// returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;

	// intoarce numarul de elemente din colectie
	int dim() const;

	// verifica daca colectia e vida;
	bool vida() const;

	// returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

};