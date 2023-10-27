#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;


bool rel(TElem e1, TElem e2)
{
	if (e1 <= e2)
		return true;
	return false;
}


// Nod
Nod::Nod(TElem e, PNod urm)
{
	/// <summary>
	/// Constructorul clasei Nod
	/// </summary>
	/// <param name="e"> Valoarea elementului ce va fi stocat in nod (int) </param>
	/// <param name="urm"> Pointer catre urmatorul nod al colectiei (Nod*) </param>

	this->el = e;
	this->frecv = 1;
	this->urm = urm;
}

TElem Nod::element()
{
	/// <summary>
	/// Returneaza elementul din nodul curent
	/// </summary>

	return el;
}

int Nod::frecventa()
{
	/// <summary>
	/// Returneaza numarul de aparitii a elementului din nodul curent in colectie
	/// </summary>

	return frecv;
}

PNod Nod::urmator()
{
	/// <summary>
	/// Returneaza pointerul catre urmatorul nod din LSI-ul asociat colectie
	/// </summary>

	return urm;
}


// Colectie
Colectie::Colectie()
{
	/// <summary>
	/// Constructorul clasei Colectie
	/// </summary>

	prim = nullptr;
	len = 0;
}

void Colectie::adauga(TElem e)
{
	/// <summary>
	/// Adaugam un nou element la colectie
	/// Complexitate: O(n)
	/// </summary>
	/// <param name="e"> Elementul ce urmeaza a fi adaugat (TElem) </param>

	this->len++;  // incrementam nr de elemente al colectiei

	// utilizam doi pointeri la noduri pentru a
	// salva nodul curent si cel anterior
	PNod anterior = nullptr;
	PNod curent = prim;

	// parcurgem lista de noduri a colectiei cat timp
	// elementele impreuna cu cel dat respecta relatia impusa
	while (curent != nullptr && rel(curent->el, e))
	{
		if (curent->el == e)  // daca elementul mai exista deja in lista
		{					  // incrementam nr de aparitii al acestuia
			curent->frecv++;
			return;
		}

		// trecem la urmatorul nod
		anterior = curent;
		curent = curent->urm;
	}

	// elementul nu apare deloc in colectie
	// si va trebui creat un nou nod pt acesta
	PNod q = new Nod(e, nullptr);

	
	if (anterior == nullptr)  // adaugam inainte de primul element
	{
		q->urm = prim;
		prim = q;
		return;
	}

	
	if (curent == nullptr)  // adaugam dupa ultimul element
	{
		anterior->urm = q;
		q->urm = nullptr;
		return;
	}

	// adaugam intre elementul anterior si cel curent
	q->urm = curent;
	anterior->urm = q;

}

bool Colectie::sterge(TElem e)
{
	/// <summary>
	/// Sterge un element din colectie
	/// Complexitate: O(n)
	/// </summary>
	/// <param name="e"> Elementul ce va fi sters din colectie (TElem) </param>
	/// <returns> (bool)
	/// true - daca elementul s-a sters cu succes
	/// false - altfel
	/// </returns>

	// utilizam doi pointeri la noduri pentru a
	// salva nodul curent si cel anterior
	PNod anterior = nullptr;
	PNod curent = prim;

	// parcurgem lista de noduri a colectiei
	while (curent != nullptr)
	{
		if (e == curent->el)  // daca gasim un nod cu element egal cu cel dat
		{
			if (curent->frecv > 1)  // daca elementul apare de mai multe ori in colectie
			{
				curent->frecv--;  // stergem o aparitie a acestuia
			}
			else  // elementul apare o singura data in colectie => stergem nodul
			{
				if (anterior == nullptr)  // daca nodul este primul din colectie
				{
					PNod p = curent;
					prim = curent->urm;  // setam prim la urmatorul nod
					delete p;			 // dealocam spatiul pt nodul curent
				}
				else
				{
					PNod p = curent;
					anterior->urm = curent->urm;  // eliminam din lista nodul curent (sarim peste el)
					delete p;					  // dealocam spatiul pentru nodul curent
				}
			}
			
			this->len--;  // decrementam nr de elem ale colectiei
			return true;  // elementul s-a sters cu succes
		}

		// trecem la urmatorul nod
		anterior = curent;
		curent = curent->urm;
	}
	return false;  // elementul nu exista in lista
}

bool Colectie::cauta(TElem elem) const
{
	/// <summary>
	/// Determina daca un element se afla in colectie sau nu
	/// Complexitate: O(n)
	/// </summary>
	/// <param name="elem"> Elementul ce se cauta in colectie (TElem) </param>
	/// <returns> (bool)
	/// true - daca elementul se gaseste in colectie
	/// false - altfel
	/// </returns>

	// parcurgem lista de noduri a colectiei
	PNod p = prim;
	while (p != nullptr)
	{
		if (p->el == elem) // daca am gasit un nod a carui element este
			return true;   // egal cu cel dat returnam adevarat
		p = p->urm;
	}
	return false; // daca am parcurs colectia si nu am gasit elementul returnam false
}

int Colectie::nrAparitii(TElem elem) const
{
	/// <summary>
	/// Returneaza numarul de aparitii unui element dat
	/// Complexitate: O(n)
	/// </summary>
	/// <param name="elem"> Elementul pentru care se cauta numarul de aparitii (TElem)</param>
	/// <returns> (int)
	/// Numarul de aparitii a elementului respectiv in colectie (0 daca acesta nu exista in colectie)
	/// </returns>

	// parcurgem lista de noduri a colectiei
	PNod p = prim;
	while (p != nullptr)
	{
		if (p->el == elem)	  // daca am gasit un nod a carui element este egal cu cel dat
			return p->frecv;  // returnam frecventa elementului respectiv
		p = p->urm;
	}
	return 0;  // daca elementul dat nu se gaseste in lista returnam 0
}

int Colectie::dim() const
{
	/// <summary>
	/// Returneaza dimensiunea colectiei
	/// Complexitate: Theta(1)
	/// </summary>
	/// <returns> (int)
	/// Numarul total de elemente din colectie
	/// </returns>

	return len;
}

bool Colectie::vida() const
{
	/// <summary>
	/// Verifica daca colectia este vida (nu contine niciun element)
	/// Complexitate: Theta(1)
	/// </summary>
	/// <returns> (bool)
	/// true - daca colectie este vida
	/// false - altfel
	/// </returns>

	// daca pointerul spre primul nod al listei este null
	// atunci colectia nu contine niciun element
	if (prim == nullptr)
		return true;
	return false;
}

void Colectie::adaugaAparitiiMultiple(int nr, TElem elem)
{
	/// <summary>
	/// Adaugam un nou element la colectie, de un anumit numar de ori
	/// Complexitate: O(n)
	/// THROWS: exception daca nr este mai mic decat 0
	/// </summary>
	/// <param name="nr"> Numarul de adaugari a elementului dat (int) </param>
	/// <param name="elem"> Elementul ce se va adauga in colectie (TElem) </param>

	if (nr < 1)
		throw std::exception();
	
	this->len += nr;  // crestem numarul de elemente

	// utilizam doi pointeri la noduri pentru a
	// salva nodul curent si cel anterior
	PNod anterior = nullptr;
	PNod curent = prim;

	// parcurgem lista de noduri a colectiei cat timp
	// elementele impreuna cu cel dat respecta relatia impusa
	while (curent != nullptr && rel(curent->el, elem))
	{
		if (curent->el == elem)  // daca elementul mai exista deja in lista
		{						 // adaugam noul nr de aparitii al acestuia
			curent->frecv += nr;
			return;
		}

		// trecem la urmatorul nod
		anterior = curent;
		curent = curent->urm;
	}

	// elementul nu apare deloc in colectie
	// si va trebui creat un nou nod pt acesta
	PNod q = new Nod(elem, nullptr);
	
	q->frecv = nr;  // setam numarul de aparitii al elementului la cel dat

	if (anterior == nullptr)  // adaugam inainte de primul element
	{
		q->urm = prim;
		prim = q;
		return;
	}


	if (curent == nullptr)  // adaugam dupa ultimul element
	{
		anterior->urm = q;
		q->urm = nullptr;
		return;
	}

	// adaugam intre elementul anterior si cel curent
	q->urm = curent;
	anterior->urm = q;
}


IteratorColectie Colectie::iterator() const 
{
	/// <summary>
	/// Creeaza un iterator pentru colectie curenta
	/// Complexitate: Theta(1)
	/// </summary>
	/// <returns>
	/// Returneaza un iterator ce indica spre colectia curenta
	/// </returns>

	return IteratorColectie(*this);
}

Colectie::~Colectie()
{
	/// <summary>
	/// Destructorul clasei Colectie
	/// </summary>

	// parcurgem fiecare nod al LSI-ului si dealocam spatiul pentru acestea
	while (prim != nullptr)
	{
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}
}