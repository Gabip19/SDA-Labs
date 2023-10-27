#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>


IteratorColectie::IteratorColectie(const Colectie& c): col(c)
{
	/// <summary>
	/// Constructorul iteratorului pe colectie
	/// Complexitate: Theta(h), h = inaltimea arborelui
	/// </summary>
	/// <param name="c"> Colectia pe care o va itera </param>

	curent = col.rad;	// setez nodul curent la radacina
	aparitie = 1;		// setez numarul de aparitii la prima aparitie

	while (curent != nullptr)
	{
		stiva.push(curent);		// adaug in stiva elementele
		curent = curent->st;	// din arborele stanga pana la cel mai mic element
	}

	if (!stiva.empty())			// curent va indica spre ultimul element din stiva
		curent = stiva.top();	// adica cel mai mic element in raport cu relatia
}


TElem IteratorColectie::element() const
{
	/// <summary>
	/// Returneaza valoarea elementului spre care indica iteratorul
	/// Complexitate: Theta(1)
	/// THROWS: exceptie daca iteratorul nu este valid
	/// </summary>

	if (!valid())
		throw std::exception();
	return curent->el.val;
}


bool IteratorColectie::valid() const
{
	/// <summary>
	/// Verifica daca iteratorul este valid 
	/// (indica spre un element existent in colectie)
	///	Complexitate: Theta(1)
	/// </summary>
	/// <returns>
	/// True - daca iteratorul este valid
	/// False - altfel
	/// </returns>

	return curent != nullptr;
}


void IteratorColectie::urmator()
{
	/// <summary>
	/// Muta iteratorul pe urmatorul element din colectie
	/// Complexitate: O(h), h = inaltimea arborelui
	/// THROWS: exceptie daca iteratorul nu este valid
	/// </summary>

	if (!valid())
		throw std::exception();
	
	if (aparitie < curent->el.frec)	// daca nu am terminat cu toate aparitiile elementului
		aparitie++;					// trec la urmatoarea aparitie
	else	// trebuie sa mut curent
	{
		stiva.pop();				// scot elementul curent din stiva
		if (curent->dr != nullptr)	// daca are subarbore drept elementul curent
		{
			curent = curent->dr;	// mut curent pe subarborele drept
			while (curent != nullptr)
			{
				stiva.push(curent);		// adaug in stiva toate elementele din stanga
				curent = curent->st;	// pana la cel mai mic
			}
		}
		if (!stiva.empty())
		{
			curent = stiva.top();		// curent va fi ultimul element introdus in stiva
			aparitie = 1;				// setez aparitia la prima
		}
		else
			curent = nullptr;			// daca stiva e goala am depasit colectia
	}
}


void IteratorColectie::prim()
{
	/// <summary>
	/// Muta iteratorul pe primul element din colectie
	/// Complexitate: Theta(h), h = inaltimea arborelui
	/// </summary>

	curent = col.rad;	// setez elementul curent la radacina
	aparitie = 1;		// setez nr de aparitii la prima aparitie

	while (curent != nullptr)
	{
		stiva.push(curent);		// adaug nodurile in stiva
		curent = curent->st;	// in timp ce ma deplasez spre cel mai mic element din colectie
	}

	if (!stiva.empty())
		curent = stiva.top();	// elementul curent va fi ultimul element introdus in stiva
}