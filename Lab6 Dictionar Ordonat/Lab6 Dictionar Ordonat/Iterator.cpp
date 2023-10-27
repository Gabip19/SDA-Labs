#include "Iterator.h"
#include "DO.h"
#include <algorithm>

using namespace std;
using std::sort;


Iterator::Iterator(const DO& d) : dict{ d }
{
	/// <summary>
	/// Creeaza un iterator pe un dictionar ordonat
	/// Complexitate: Theta(m) creare vector cu perechi
	///				  O(n*log(n)) sortare vector
	///				  Total: O(m + n*log(n)) (n <= m)
	/// </summary>
	/// <param name="d">
	/// Referinta la dictionarul ordonat pe care se creeaza iteratorul
	/// </param>

	/// parcurgem tabela de perechi si le adaugam
	/// in vector doar pe acelea ce sunt valide
	for (int i = 0; i < dict.m; i++)
	{
		if (dict.tabela[i].first != NULL_TCHEIE && dict.tabela[i].first != CHEIE_STEARSA)
			do_pairs.push_back(dict.tabela[i]);
	}
	
	/// sortam veectorul perechilor in functie de cheie
	/// si de relatia dintre acestea stabilita in dictionar
	Relatie rel_sort = dict.rel;
	sort(
		do_pairs.begin(), 
		do_pairs.end(), 
		[&rel_sort](const TElem& pr1, const TElem& pr2) {
			if (rel_sort(pr1.first, pr2.first))
				return true;
			return false;
		}
	);

	/// setam iteratorul la prima pereche din vector
	curent = 0;
}


void Iterator::prim()
{
	/// <summary>
	/// Reseteaza iteratorul la prima pereche din dictionar
	/// Complexitate: Theta(1)
	/// </summary>

	curent = 0;
}


void Iterator::urmator()
{
	/// <summary>
	/// Muta iteratorul la urmatoarea pereche din dictionar
	/// Complexitate: Theta(1)
	/// </summary>

	if (!valid())
		throw std::exception();
	curent++;
}


bool Iterator::valid() const
{
	/// <summary>
	/// Verifica daca iteratorul nu a depasit numarul
	/// perechilor din dictionar
	/// Complexitate: Theta(1)
	/// </summary>
	/// <returns> 
	/// True - daca iteratorul mai este valid
	/// False - altfel
	/// </returns>

	return curent < do_pairs.size();
}


TElem Iterator::element() const
{
	/// <summary>
	/// Returneaza elementul curent indicat de iterator
	/// Complexitate: Theta(1)
	/// </summary>
	/// <returns>
	/// Perechea curenta din dictionar
	/// </returns>

	if (!valid())
		throw std::exception();
	return do_pairs.at(curent);
}