#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>


IteratorColectie::IteratorColectie(const Colectie& c) : col(c)
{
	/// <summary>
	/// Constructorul pentru iteratorul unei colectii
	/// Complexitate: Theta(1)
	/// </summary>
	/// <param name="c"> (referinta Colectie)
	/// Colectia pentru care se creeaza iteratorul
	/// </param>

	curent = col.prim;
	aparitie = 1;
}


TElem IteratorColectie::element() const
{
	/// <summary>
	/// Returneaza valoarea elementului din container referit de iterator
	/// Complexitate: Theta(1)
	/// THROWS: exception daca iteratorul nu este valid
	/// </summary>
	/// <returns> (TElem)
	/// Elementul referit de iterator
	/// </returns>

	if (!valid())
		throw std::exception();

	// returnam elementul din nodul referit de iterator la momentul actual
	return col.elem[curent].el;
}


bool IteratorColectie::valid() const
{
	/// <summary>
	/// Verifica daca iteratorul e valid (indica un element al containerului)
	/// Complexitate: Theta(1)
	/// </summary>
	/// <returns>
	/// true - daca iteratorul este valid
	/// false - altfel
	/// </returns>

	// daca elementul curent este -1 atunci
	// am terminat de parcurs elementele colectiei
	return curent != -1;
}


void IteratorColectie::urmator()
{
	/// <summary>
	/// Muta iteratorul in container
	/// Complexitate: Theta(1)
	/// THROWS: exception daca iteratorul nu mai este valid
	/// </summary>

	if (!valid())
		throw std::exception();

	if (aparitie < col.elem[curent].frecv)  // verificam daca am parcurs toate instantele
	{									    // unui element in colectie
		aparitie++;  // daca nu trecem la urmatoarea aparitie a elementului
	}
	else  // altfel
	{
		curent = col.urm[curent];    // trecem la urmatorul nod din lista colectiei
		aparitie = 1;				 // resetam contorul pentru nr de aparitii
	}
}


void IteratorColectie::prim()
{
	/// <summary>
	/// Reseteaza pozitia iteratorului la inceputul containerului
	/// Complexitate: Theta(1)
	/// </summary>

	curent = col.prim;
	aparitie = 1;
}