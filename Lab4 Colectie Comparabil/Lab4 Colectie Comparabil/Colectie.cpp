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


// Colectie

Colectie::Colectie()
{
	/// <summary>
	/// Constructorul clasei Colectie
	/// Complexitate: Theta(n) - n capacitatea colectiei la initializare
	/// in cazul de fata Theta(1)
	/// </summary>

	cp = 1;
	len = 0;
	elem = new TElemCol[cp];
	urm = new int[cp];

	// completam vectorul de pozitii ca fiind liber
	for (int i = 0; i < cp - 1; i++)
	{
		urm[i] = i + 1;
	}
	urm[cp - 1] = -1;
	prim = -1;
	primLiber = 0;
}


int Colectie::aloca()
{
	/// <summary>
	/// Marcheaza un nod din lista ca fiind ocupat
	/// Complexitate: Theta(1)
	/// </summary>
	/// <returns> Returneaza pozitia nodului ce a fost marcat ca ocupat </returns>

	int i = primLiber;			 // primul nod liber va fi ocupat
	primLiber = urm[primLiber];  // primulLiber va fi urmatorul nod
	return i;
}


void Colectie::dealoca(int i)
{
	/// <summary>
	/// Marcheaza un nod dat ca fiind liber
	/// Complexitate: Theta(1)
	/// </summary>
	
	urm[i] = primLiber;  // actualul primLiber se muta pe poz urmatoare
	primLiber = i;		 // actualizam primLiber
}


int Colectie::creeazaNod(TElem el)
{
	/// <summary>
	/// Creeaza un nou nod in lista cu valoarea elementului dat
	/// Complexitate: Theta(1) amortizat
	/// </summary>
	/// <returns> Pozitia din vector unde s-a creat nodul </returns>
	
	if (primLiber == -1)	// daca nu mai avem noduri libere
		redim();			// redimensionam vectorii

	int i = aloca();		// alocam spatiu pentru noul nod

	TElemCol el_nou{};
	el_nou.el = el;			// setam valoarea
	el_nou.frecv = 1;		// setam frecventa

	elem[i] = el_nou;		// punem elementul pe pozitia alocata
	urm[i] = -1;			// marcam nodul urmator ca fiind inexistent

	return i;				// returnam pozitia unde s-a creat nodul
}


void Colectie::redim()
{
	/// <summary>
	/// Mareste capacitatea de stocare a vectorilor asociati implementarii colectiei
	/// Complexitate: Theta(n), n - noua capacitatea a vectorului dupa redimensionare
	/// </summary>

	int cp_nou = cp * 2;	// dublam capacitatea
	TElemCol* elem_nou = new TElemCol[cp_nou];
	int* urm_nou = new int[cp_nou];

	// copiem toate elementele din vectorii actuali in cei noi
	for (int i = 0; i < cp; ++i)
	{
		elem_nou[i] = elem[i];
		urm_nou[i] = urm[i];
	}

	// marcam toate pozitiile noi adaugate ca facand 
	// parte din vectorul de pozitii libere fiind consecutive
	for (int i = cp; i < cp_nou - 1; ++i)
	{
		urm_nou[i] = i + 1;
	}
	urm_nou[cp_nou - 1] = -1;  // ultima pozitie nu are niciun succesor

	this->primLiber = cp;	   // setam primLiber la primul element nou dupa redim

	delete[] elem;
	delete[] urm;

	// actualizam proprietatile colectiei
	this->elem = elem_nou;
	this->urm = urm_nou;
	this->cp = cp_nou;
}


void Colectie::adauga(TElem e)
{
	/// <summary>
	/// Adaugam un nou element la colectie
	/// Complexitate: O(n)
	/// </summary>
	/// <param name="e"> Elementul ce urmeaza a fi adaugat (TElem) </param>

	this->len++;

	int anterior = -1;
	int curent = prim;

	// parcurgem lista de noduri a colectiei cat timp
	// elementele impreuna cu cel dat respecta relatia impusa
	while (curent != -1 && rel(elem[curent].el, e))
	{
		if (elem[curent].el == e)  // daca elementul mai exista deja in lista
		{						   // incrementam nr de aparitii al acestuia
			elem[curent].frecv++;
			return;
		}

		// trecem la urmatorul nod
		anterior = curent;
		curent = urm[curent];
	}

	// elementul nu apare deloc in colectie
	// si va trebui creat un nou nod pt acesta
	int i = creeazaNod(e);


	if (anterior == -1)  // adaugam inainte de primul element
	{
		urm[i] = prim;
		prim = i;
		return;
	}


	if (curent == -1)  // adaugam dupa ultimul element
	{
		urm[anterior] = i;
		urm[i] = -1;
		return;
	}


	// adaugam intre elementul anterior si cel curent
	urm[i] = curent;
	urm[anterior] = i;
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

	int anterior = -1;
	int curent = prim;

	// parcurgem lista de noduri a colectiei
	while (curent != -1 && rel(elem[curent].el, e))
	{
		if (e == elem[curent].el)  // daca gasim un nod cu element egal cu cel dat
		{
			if (elem[curent].frecv > 1)  // daca elementul apare de mai multe ori in colectie
			{
				elem[curent].frecv--;  // stergem o aparitie a acestuia
			}
			else  // elementul apare o singura data in colectie => stergem nodul
			{
				if (anterior == -1)  // daca nodul este primul din colectie
				{
					prim = urm[curent];  // setam prim la urmatorul nod
					dealoca(curent);	 // dealocam spatiul pt nodul curent
				}
				else
				{
					urm[anterior] = urm[curent];  // eliminam din lista nodul curent (sarim peste el)
					dealoca(curent);			  // dealocam spatiul pentru nodul curent
				}
			}

			this->len--;  // decrementam nr de elem al colectiei
			return true;  // elementul s-a sters cu succes
		}

		// trecem la urmatorul nod
		anterior = curent;
		curent = urm[curent];
	}
	return false;  // elementul nu exista in lista
}


int Colectie::eliminaAparitii(int nr, TElem el)
{
	/// <summary>
	/// Sterge nr aparitii element din colectie
	/// Complexitate: O(n)
	/// </summary>
	/// <param name="e"> Elementul ce va fi sters de nr ori </param>
	/// <returns> (int)
	/// true - daca elementul s-a sters cu succes
	/// false - altfel
	/// </returns>

	if (nr <= 0)
		throw std::exception();

	int anterior = -1;
	int curent = prim;

	// parcurgem lista de noduri a colectiei
	while (curent != -1 && rel(elem[curent].el, el))
	{
		if (el == elem[curent].el)  // daca gasim un nod cu element egal cu cel dat
		{
			if (elem[curent].frecv > nr)  // daca elementul apare de mai multe ori in colectie
			{
				elem[curent].frecv -= nr; 
				this->len -= nr;
				return nr;
			}
			else  // elementul apare o singura data in colectie => stergem nodul
			{	  // elem[curent].frecv <= nr
				int rez = elem[curent].frecv;
				
				if (anterior == -1)  // daca nodul este primul din colectie
				{
					prim = urm[curent];  // setam prim la urmatorul nod
					dealoca(curent);	 // dealocam spatiul pt nodul curent
				}
				else
				{
					urm[anterior] = urm[curent];  // eliminam din lista nodul curent (sarim peste el)
					dealoca(curent);			  // dealocam spatiul pentru nodul curent
				}

				this->len -= rez;
				return rez;
			}
		}

		// trecem la urmatorul nod
		anterior = curent;
		curent = urm[curent];
	}
	return 0;  // elementul nu exista in lista
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
	int p = prim;
	while (p != -1 && rel(this->elem[p].el, elem))
	{
		if (this->elem[p].el == elem) // daca am gasit un nod a carui element este
			return true;			  // egal cu cel dat returnam adevarat
		p = urm[p];		// trecem la urmatorul nod
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
	int p = prim;
	while (p != -1 && rel(this->elem[p].el, elem))
	{
		if (this->elem[p].el == elem)	  // daca am gasit un nod a carui element este egal cu cel dat
			return this->elem[p].frecv;   // returnam frecventa elementului respectiv
		p = urm[p];		// trecem la urmatorul nod
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
	/// true - daca colectia este vida
	/// false - altfel
	/// </returns>

	// daca primul nod al listei este inexistent (= -1)
	// atunci colectia nu contine niciun element
	if (prim == -1)
		return true;
	return false;
}


//void Colectie::adaugaAparitiiMultiple(int nr, TElem elem)
//{
//	/// <summary>
//	/// Adaugam un nou element la colectie, de un anumit numar de ori
//	/// Complexitate: O(n)
//	/// THROWS: exception daca nr este mai mic decat 0
//	/// </summary>
//	/// <param name="nr"> Numarul de adaugari a elementului dat (int) </param>
//	/// <param name="elem"> Elementul ce se va adauga in colectie (TElem) </param>
//
//	if (nr < 1)
//		throw std::exception();
//
//	this->len += nr;  // crestem numarul de elemente
//
//	// utilizam doi pointeri la noduri pentru a
//	// salva nodul curent si cel anterior
//	PNod anterior = nullptr;
//	PNod curent = prim;
//
//	// parcurgem lista de noduri a colectiei cat timp
//	// elementele impreuna cu cel dat respecta relatia impusa
//	while (curent != nullptr && rel(curent->el, elem))
//	{
//		if (curent->el == elem)  // daca elementul mai exista deja in lista
//		{						 // adaugam noul nr de aparitii al acestuia
//			curent->frecv += nr;
//			return;
//		}
//
//		// trecem la urmatorul nod
//		anterior = curent;
//		curent = curent->urm;
//	}
//
//	// elementul nu apare deloc in colectie
//	// si va trebui creat un nou nod pt acesta
//	PNod q = new Nod(elem, nullptr);
//
//	q->frecv = nr;  // setam numarul de aparitii al elementului la cel dat
//
//	if (anterior == nullptr)  // adaugam inainte de primul element
//	{
//		q->urm = prim;
//		prim = q;
//		return;
//	}
//
//
//	if (curent == nullptr)  // adaugam dupa ultimul element
//	{
//		anterior->urm = q;
//		q->urm = nullptr;
//		return;
//	}
//
//	// adaugam intre elementul anterior si cel curent
//	q->urm = curent;
//	anterior->urm = q;
//}


IteratorColectie Colectie::iterator() const
{
	/// <summary>
	/// Creeaza un iterator pentru colectia curenta
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
	/// Complexitate: Theta(1)
	/// </summary>

	delete[] elem;	// dealocam spatiu vector elemente
	delete[] urm;	// dealocam spatiu vector pozitii urmatoare
}