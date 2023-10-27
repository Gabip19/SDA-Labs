
#include "Coada.h"
#include <exception>
#include <iostream>

using namespace std;


Coada::Coada() 
{
	/// <summary>
	/// Constructorul clasei Coada
	/// </summary>

	this->cp = 3;
	this->fata = 0;
	this->spate = 0;
	
	// alocam dinamic vectorul ce va stoca elementele cozii
	this->elems = new TElem[this->cp];
}


void Coada::adauga(TElem elem) 
{
	/// <summary>
	/// Adauga un element in coada
	/// Complexitate: Theta(1)
	/// </summary>
	/// <param name="elem"> (TElem)
	/// Elementul ce va fi adaugat in coada
	/// </param>

	// verificam daca coada a atins capacitatea maxima
	if ((fata == 0 && spate == cp - 1) || (fata == spate + 1))
		redim(); // in caz afirmativ marim capacitatea cozii

	// elementul se adauga la finalul cozii
	elems[spate] = elem;

	
	if (spate == cp - 1)
		spate = 0; // daca spatele a ajuns pe pozitia finala, il mutam la inceput (coada circulara)
	else
		spate++; // daca nu, incrementam valoarea spatelui
}


TElem Coada::element() const
{
	/// <summary>
	/// Returneaza primul element din coada
	/// Complexitate: Theta(1)
	/// </summary>
	/// <returns> (TElem)
	/// Returneaza elementul aflat pe prima pozitie in cadrul cozii
	/// THROWS: runtime_error exception daca coada este vida
	/// </returns>

	// verificam daca coada este vida
	if (vida())
		throw std::exception();

	TElem e = elems[fata];
	return e;
}


TElem Coada::sterge() 
{
	/// <summary>
	/// Sterge primul element din coada (principiul FIFO)
	/// Complexitate: Theta(1)
	/// </summary>
	/// <returns> (TElem)
	/// Returneaza elementul ce tocmai a fost sters din lista
	/// THROWS: runtime_error exception daca coada este vida
	/// </returns>

	// obtinem primul element din lista
	TElem e = element();
	
	// mutam fata la al doilea element din coada
	if (fata == cp - 1)
		fata = 0; // daca se sterge elementul de pe ultima pozitie din vectorul alocat, resetam fata
	else
		fata++; // in caz contrar incrementam fata
	return e;
}


bool Coada::vida() const
{
	/// <summary>
	/// Verifica daca coada este vida (nu contine niciun element = depasire inferioara) 
	/// Complexitate: Theta(1)
	/// </summary>
	/// <returns> (bool)
	/// true - Daca coada nu contine niciun element (inceputul si sfarsitul cozii coincid)
	/// false - In caz contrar
	/// </returns>

	return fata == spate;
}


Coada::~Coada()
{
	/// <summary>
	/// Destructorul clasei Coada
	/// </summary>

	// eliberam spatiul ocupat de vectorul dinamic
	delete[] this->elems;
}


void Coada::redim()
{
	/// <summary>
	/// Redimensionam vectorul ce contine elementele 
	/// cozii in caz de depasire superioara
	/// Complexitate: Theta(n), n = numarul actual de elemente din coada
	/// </summary>

	// alocam spatiu pentru noul vector (dublam capacitatea de stocare)
	TElem* new_elems = new TElem[cp * 2];
	int k = 0;

	if (fata < spate)
	{
		// daca pentru coada circulara in cadrul vectorului dinamic
		// fata se afla afla inaintea spatelui, parcurgem toate elementele
		// si le copiem in noul vector de la pozitia 0

		for (int i = fata; i < spate; ++i)
		{
			new_elems[k++] = elems[i];
		}
	}
	else if (fata > spate)
	{
		// in caz contrat parcurgem toate elementele de la fata pana
		// la ultima pozitie din vector si le copiem incepand cu pozitia 0
		// in noul vector, dupa care parcurgem si elementele de la inceput
		// pana la spate pentru a pastra ordinea acestora

		for (int i = fata; i < cp; ++i)
		{
			new_elems[k++] = elems[i];
		}
		for (int i = 0; i < spate; ++i)
		{
			new_elems[k++] = elems[i];
		}
	}

	// dublam capacitatea
	cp = 2 * cp;
	// actualizam fata si spatele cozii
	fata = 0;
	spate = k;

	// eliberam memoria ocupata de vechiul vector
	delete[] elems;

	// actualizam vectorul asociat cozii
	elems = new_elems;
}