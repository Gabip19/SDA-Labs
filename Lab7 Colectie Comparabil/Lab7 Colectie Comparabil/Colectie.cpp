#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>
#include <exception>

using namespace std;


bool rel(TElem e1, TElem e2)
{
	if (e1 <= e2)
		return true;
	return false;
}


Nod::Nod(TElem el, PNod st, PNod dr)
{
	/// <summary>
	/// Creeaza un nod
	/// Complexitate: Theta(1)
	/// </summary>
	/// <param name="el"> valoarea elementului de tip TElemCol </param>
	/// <param name="st"> radacina subarborelui stang </param>
	/// <param name="dr"> radacina subarborelui drept </param>

	this->el.val = el;
	this->el.frec = 1;
	this->st = nullptr;
	this->dr = nullptr;
	this->parinte = nullptr;
}


Colectie::Colectie()
{
	/// <summary>
	/// Constructorul colectiei
	/// Complexitate: Theta(1)
	/// </summary>

	this->rad = nullptr;
	this->nr = 0;
}


PNod Colectie::adauga_rec(PNod p, TElem e)
{
	/// <summary>
	/// Adauga recursiv elementul cu valoarea data in subarborele
	/// cu radacina data
	/// Complexitate: O(h), h = inaltimea arborelui
	/// </summary>
	/// <param name="p"> Radacina arborelui in care se va adauga elementul </param>
	/// <param name="e"> Valoarea elementului ce se va adauga </param>
	/// <returns> Returneaza radacina noului subarbore </returns>

	if (p == nullptr)
	{
		/// daca pointer-ul este null valoarea nu exista
		/// deci alocam un nod nou pentru ea
		p = new Nod(e, nullptr, nullptr);
	}
	else
	{
		if (p->el.val == e)
		{
			/// daca valoarea exista deja cresc frecventa
			p->el.frec++;
		}
		else
		{
			if (rel(e, p->el.val))
			{
				// valoare mai mica -> adaug in stanga
				p->st = adauga_rec(p->st, e);
				p->st->parinte = p;
			}
			else
			{
				// valoare mai mare -> adaug in dreapta
				p->dr = adauga_rec(p->dr, e);
				p->dr->parinte = p;
			}
		}
	}
	return p;
}


PNod Colectie::adauga_rec_multiple(PNod p, TElem e, int nr)
{
	/// <summary>
	/// Adauga recursiv nraparitii ale elementului cu valoarea data in subarborele
	/// cu radacina data
	/// Complexitate: O(h), h = inaltimea arborelui
	/// </summary>
	/// <param name="p"> Radacina arborelui in care se va adauga elementul </param>
	/// <param name="e"> Valoarea elementului ce se va adauga </param>
	/// <param name="nr> Nr de aparitii al elementului </param>
	/// <returns> Returneaza radacina noului subarbore </returns>

	if (p == nullptr)
	{
		// daca pointer-ul este null valoarea nu exista
		// deci alocam un nod nou pentru ea
		p = new Nod(e, nullptr, nullptr);
		p->el.frec = nr;
	}
	else
	{
		if (p->el.val == e)
		{
			// daca valoarea exista deja cresc frecventa
			p->el.frec += nr;
		}
		else
		{
			if (rel(e, p->el.val))
			{
				// valoare mai mica -> adaug in stanga
				p->st = adauga_rec_multiple(p->st, e, nr);
				p->st->parinte = p;
			}
			else
			{
				// valoare mai mare -> adaug in dreapta
				p->dr = adauga_rec_multiple(p->dr, e, nr);
				p->dr->parinte = p;
			}
		}
	}
	return p;
}


void Colectie::adaugaAparitiiMultiple(int nr, TElem elem)
{
	if (nr <= 0)
		throw std::exception();

	rad = adauga_rec_multiple(rad, elem, nr);
}


void Colectie::adauga(TElem e)
{
	/// <summary>
	/// Adauga un element in colectie
	/// Complexitate: O(h), h = inaltimea arborelui
	/// </summary>
	/// <param name="e"> Valoarea elementului </param>
	
	rad = adauga_rec(rad, e);	// adaug elementul
	nr++;						// cresc numarul de elemente din colectie
}


PNod Colectie::minim(PNod p)
{
	/// <summary>
	/// Determina valoarea minima dintr-un arbore cu radacina data
	/// Complexitate: O(h), h = inaltimea arborelui
	/// </summary>
	/// <param name="p"> Radacina arborelui </param>
	/// <returns>
	/// Returneaza valoarea minima din acel arbore 
	/// (cea mai din stanga valoare din arbore)
	/// </returns>

	while (p->st != nullptr)
	{
		p = p->st;
	}
	return p;
}


////////////////////////////////////////////////////////////////
PNod Colectie::sterge_rec(PNod p, TElem e, bool& sters)
{
	if (p == nullptr)
		return nullptr;
	if (e == p->el.val)
	{
		if (p->el.frec > 1)
		{
			p->el.frec--;
			nr--;
			sters = true;
			return p;
		}
		else
		{
			if (p->st != nullptr && p->dr != nullptr)
			{
				PNod temp = minim(p->dr);
				p->el = temp->el;
				temp->el.frec = 1;
				p->dr = sterge_rec(p->dr, temp->el.val, sters);
				return p;
			}
			else
			{
				PNod value = nullptr;
				if (p->st == nullptr)
					value = p->dr;
				else if (p->dr == nullptr)
					value = p->st;

				delete p;
				sters = true;
				nr--;
				return value;
			}
		}
	}
	else if (rel(e, p->el.val)) 
	{
		p->st = sterge_rec(p->st, e, sters);
		return p;
	}
	else 
	{
		p->dr = sterge_rec(p->dr, e, sters);
		return p;
	}
}
////////////////////////////////////////////////////////////////

/////////////////////////////////////////
bool Colectie::sterge_r(TElem e)
{
	bool sters = false;
	rad = sterge_rec(rad, e, sters);
	
	return sters;
}
/////////////////////////////////////////


bool Colectie::sterge(TElem e)
{
	/// <summary>
	/// Sterge un element din colectie
	/// Complexitate: O(h), h = inaltimea arborelui
	/// </summary>
	/// <param name="e"> Valoarea elementului ce se va sterge din colectie </param>
	/// <returns>
	/// True - daca elementul s-a sters cu succes
	/// False - daca elementul nu s-a sters (nu exista in colectie)
	/// </returns>

	PNod p = rad;

	// cat timp nu am parcurs tot subarborele
	while (p != nullptr)
	{
		if (p->el.val == e)		// daca am gasit elementul
		{
			if (p->el.frec > 1)	// daca frecventa sa este mai mare decat 1
			{	
				p->el.frec--;	// scad frecventa
				nr--;			// decrementez nr de elemente al colectiei
				return true;	// returnez true
			}
			else   // elementul apare o singura data si va trebui sters tot nodul
			{	
				if (p->st != nullptr && p->dr != nullptr)
				{	
					// daca nodul ce contine elementul are si
					// subarbore stang si subarbore drept
					
					PNod temp = minim(p->dr);	// caut cea mai mica val mai mare decat elem curent
					TElemCol aux = temp->el;	// salvez valoarea din nodul respectiv
					
					temp->el.frec = 1;			// setez frecventa minimului la 1 pt a fi sigur ca va fi sters
					sterge(temp->el.val);		// sterg nodul minim din arbore

					p->el = aux;				// mut minimul in nodul in care se afla val ce trebuia stearsa
					return true;				// nodul s-a sters -> returnez true
				}
				else
				{
					PNod parinte = p->parinte;	// salvez parintele nodului curent
					PNod value = nullptr;

					if (p->st == nullptr && p->dr == nullptr)
					{	// daca nu am subarbore stang si drept
						value = nullptr;
					}
					else if (p->st == nullptr)
					{	// daca am doar subarbore drept
						value = p->dr;				// salvez valoare nodului sau
						p->dr->parinte = parinte;	// setez parintele subarb drept la parintele nodului ce se va sterge
					}
					else if (p->dr == nullptr)
					{	// daca am doar subarbore stang
						value = p->st;				// salvez valoare nodului sau
						p->st->parinte = parinte;	// setez parintele subarb drept la parintele nodului ce se va sterge
					}

					if (parinte == nullptr)		// daca parinte = null -> sterge radacina
						rad = value;
					else if (parinte->st == p)	// daca nodul se afla in stanga parintelui
						parinte->st = value;	// actualizez stanga
					else if (parinte->dr == p)	// daca nodul se afla in dreapta parintelui
						parinte->dr = value;	// actualizez dreapta

					nr--;			// scad nr de elemente al colectiei
					delete p;		// dealoc spatiul nodului
					return true;	// nodul s-a sters cu succes -> returnez true
				}
			}
		}
		else
		{	// nu am gasit elementul inca
			if (rel(e, p->el.val))
				p = p->st;	// caut in stanga
			else
				p = p->dr;	// caut in dreapta
		}
	}
	// daca am parcurs arborele si nu am gasit valoarea
	// -> nu exista elementul -> returnez false
	return false;
}


bool Colectie::cauta(TElem elem) const
{
	/// <summary>
	/// Determina daca un element se afla in colectie
	/// Complexitate: O(h), h = inaltimea arborelui
	/// </summary>
	/// <param name="elem"> Valoarea elementului ce se va cauta in colectie </param>
	/// <returns>
	/// True - daca elementul exista in colectie
	/// False - altfel
	/// </returns>

	PNod p = rad;
	while (p != nullptr)
	{
		if (p->el.val == elem)
		{
			// daca am gasit elementul returnez true
			return true;
		}
		else
		{
			if (rel(elem, p->el.val))
				p = p->st;	// caut in stanga
			else
				p = p->dr;	// caut in dreapta
		}
	}
	// am ajuns la null si elementul nu a fost gasit => nu exista
	return false;
}


int Colectie::nrAparitii(TElem elem) const
{
	/// <summary>
	/// Returneaza numarul de aparitii a unui element in colectie
	/// Complexitate: O(h), h = inaltimea arborelui
	/// </summary>
	/// <param name="elem"> Valoarea elementului a carui nr de aparitii se va afisa </param>

	PNod p = rad;
	while (p != nullptr)
	{
		if (p->el.val == elem)
		{
			// daca am gasit elementul returnez frecventa
			return p->el.frec;
		}
		else
		{
			if (rel(elem, p->el.val))
				p = p->st;	// caut in stanga
			else
				p = p->dr;	// caut in dreapta
		}
	}
	// am ajuns la null si elementul nu a fost gasit => nu exista (nr aparitii 0)
	return 0;
}


int Colectie::dim() const
{
	/// <summary>
	/// Returneaza numarul de elemented in colectie
	/// Complexitate: Theta(1)
	/// </summary>

	return nr;
}


bool Colectie::vida() const
{
	/// <summary>
	/// Verifica daca avem o colectie vida
	/// Complexitate: Theta(1)
	/// </summary>
	/// <returns>
	/// True daca radacina nu indica spre nimic / false altfe
	/// </returns>

	return rad == nullptr;
}


IteratorColectie Colectie::iterator() const
{
	/// <summary>
	/// Returneaza un iterator pe colectie
	/// Complexitate: Theta(1)
	/// </summary>

	return IteratorColectie(*this);
}


void Colectie::distruge_rec(PNod p)
{
	/// <summary>
	/// Distruge recursiv subarborele stang si drept a unui nod
	/// Complexitate: O(h), h = inaltimea arborelui
	/// </summary>
	/// <param name="p"> Nodul ce se va sterge </param>

	if (p != nullptr)
	{
		distruge_rec(p->st);	// distrug stanga
		distruge_rec(p->dr);	// distrug dreapta
		delete p;				// sterg nodul
	}
}


Colectie::~Colectie()
{
	/// <summary>
	/// Destructorul colectiei
	/// Complexitate: O(h), h = inaltimea arborelui
	/// </summary>

	nr = 0;
	// Distruge recursiv fiecare subarbore
	distruge_rec(rad);
}