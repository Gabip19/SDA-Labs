#include "Iterator.h"
#include "DO.h"
#include <iostream>
#include <cmath>
#include <exception>

using namespace std;


int hashCode(TCheie c)
{
	/// <summary>
	/// Determina hashcode-ul
	/// Complexitate: Theta(1)
	/// </summary>
	/// <param name="c"> Cheia pentru care se calculeaza </param>
	/// <returns> Returneaza valoarea absoluta a cheii </returns>
	
	return abs(c);
}


int DO::d(TCheie c, int i) const
{
	/// <summary>
	/// Functia de dispersie
	/// (DISPERSIE DUBLA)
	/// Complexitate: Theta(1)
	/// </summary>
	/// <param name="c"> Cheia pentru care se calculeaza </param>
	/// <param name="i"> 
	/// Numarul cu care se inmulteste in calculul decalajului 
	/// </param>
	/// <returns> Returneaza dispersia cheii </returns>

	int dsp1 = hashCode(c) % m;
	int dsp2 = 1 + hashCode(c) % (m - 2);
	int rez = (dsp1 + i * dsp2) % m;
	return rez;
}


DO::DO(Relatie r) : rel{ r }
{
	/// <summary>
	/// Creeaza dictionarul
	/// Complexitate: Theta(m), m nr spatii tabela
	/// </summary>
	/// <param name="r">
	/// Relatia de care se va tine cont in ordonarea elementelor
	/// </param>

	m = 13;
	nr = 0;
	tabela = new TElem[m];

	for (int i = 0; i < m; i++)
	{	
		/// initializam toate elementele ca fiind nule
		tabela[i] = TElem(NULL_TCHEIE, NULL_TVALOARE);
	}
}


// adauga o pereche (cheie, valoare) in dictionar
// daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
// daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v)
{
	/// <summary>
	/// Adauga o pereche in dictionar
	/// Complexitate: 
	///		In ipoteza SUH: cel mult (1/(1-a)), a = factorul de incarcare al tabelei
	///						Daca a = constant -> Theta(1)
	///		Caz defavorabil: O(m)
	///		***Valabil in cazul amortizat***
	/// </summary>
	/// <param name="c"> Cheia ce se va adauga in pereche </param>
	/// <param name="v"> Valoarea ce se va adauga in pereche </param>
	/// <returns> Vechea valoare daca cheia exista / altfel NULL_TVALOARE </returns>

	/// daca tabela este plina redimensionam si rearanjam elementele
	if (nr == m)
		rehash();

	int i = 0;
	
	/// cat timp nu am parcurs toata secventa de verificare a cheii
	while (i != m)
	{
		/// calculam urmatoarea pozitie de dispersie din secventa
		int j = d(c, i);
		if (tabela[j].first == NULL_TCHEIE || tabela[j].first == CHEIE_STEARSA)
		{	
			/// verificam daca am gasit o pozitie libera (nula / stearsa)
			/// daca gasim una, setam cheia si valoarea in pereche
			tabela[j].first = c;
			tabela[j].second = v;
			
			nr++;						/// incrementam nr de perechi din dictionar
			return NULL_TVALOARE;		/// returnam NULL pt ca nu exista cheia deja
		}
		else if (tabela[j].first == c)
		{
			/// daca gasim in secventa o pereche cu acceasi cheie
			int ult_val = tabela[j].second;		/// salvam valoarea anterioara din pereche

			tabela[j].second = v;				/// updatam noua valoare din pereche

			return ult_val;						/// returnam ultima valoare din pereche
		}
		else
		{
			++i;	/// trecem la urmatoarea pereche din secventa
		}
	}

	return NULL_TVALOARE;
}


int DO::urm_prim(int num)
{
	/// <summary>
	/// Calculeaza primul numar prim mai mare decat cel dat
	/// </summary>
	/// <param name="num"> Numarul pentru care se cauta urm nr prim </param>
	/// <returns> Primul numar prim mai mare decat num </returns>

	bool done = false;
	while (!done)
	{
		done = true;
		if (num % 2 == 0)
			done = false;
		else for (int d = 3; d * d <= num; d += 2)
		{
			if (num % d == 0)
				done = false;
		}
		if (done)
			return num;
		else
			num++;
	}
}


void DO::rehash()
{
	/// <summary>
	/// Redimensioneaza tabela si recalculeaza dispersia
	/// elementelor in cadrul acesteia
	/// Complexitate:
	/// 	In ipoteza SUH: cel mult (1/(1-a)) fara succes, (1/a * ln(1/(1-a))) cu succes
	///						redispersarea unui element in noua tabela
	///						a = factorul de incarcare al tabelei
	///						Daca a = constant -> Theta(1) pt redispersia unui element
	///						Initializare tabela noua -> Theta(m) => Complexitate totala Theta(m)
	///		Caz defavorabil: O(m^2)
	/// </summary>

	int m_vechi = m;			/// salvam vechea valoare a lui m
	m = urm_prim(2 * m + 1);	/// calculam noul m

	TElem* tabela_noua = new TElem[m];

	for (int i = 0; i < m; ++i)
	{
		/// completam noua tabela cu elemente nulle
		tabela_noua[i] = TElem(NULL_TCHEIE, NULL_TVALOARE);
	}

	for (int k = 0; k < m_vechi; ++k)
	{
		/// recalculam dispersiile pentru fiecare element din vechea tabela
		/// si le adaugam la pozitia corespunzatoare in tabela noua
		int i = 0;
		int j = d(tabela[k].first, i);
		while (tabela_noua[j].first != NULL_TCHEIE)
		{
			++i;
			j = d(tabela[k].first, i);
		}
		tabela_noua[j].first = tabela[k].first;
		tabela_noua[j].second = tabela[k].second;
		/*while (i != m)
		{
			int j = d(tabela[k].first, i);
			if (tabela_noua[j].first == NULL_TCHEIE)
			{
				tabela_noua[j].first = tabela[k].first;
				tabela_noua[j].second = tabela[k].second;
				break;
			}
			else
			{
				++i;
			}
		}*/
	}

	/// actualizam tabela
	delete[] tabela;
	tabela = tabela_noua;
}


//////////////////
void DO::afis()
{
	for (int i = 0; i < m; i++)
	{
		if (tabela[i].first == NULL_TCHEIE)
			cout << "(NULL, " << tabela[i].second << "), ";
		else if (tabela[i].first == CHEIE_STEARSA)
			cout << "(STERS, " << tabela[i].second << "), ";
		else
			cout << "(" << tabela[i].first << ", " << tabela[i].second << "), ";
			
	}
	cout << "\n\n";
}
//////////////////


//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const
{
	/// <summary>
	/// Cauta o cheie in dictionar
	/// Complexitate:
	/// 	In ipoteza SUH: cel mult (1/(1-a)) fara succes, (1/a * ln(1/(1-a))) cu succes
	///						a = factorul de incarcare al tabelei
	///						Daca a = constant -> Theta(1)
	///		Caz defavorabil: O(m)
	/// </summary>
	/// <param name="c"> Cheie ce se va cauta </param>
	/// <returns> Valoarea asociata cheii daca aceasta exista / altfel NULL_TVALOARE </returns>

	int i = 0;
	
	/// parcurgem toata secventa de verificare a cheii
	while (i != m)
	{
		/// calculam urmatoarea pozitie de dispersie din secventa
		int j = d(c, i);
		if (tabela[j].first == c)		/// daca am gasit cheia
			return tabela[j].second;	/// returnam valoarea
		else if (tabela[j].first == NULL_TCHEIE)	/// daca am intalnit null in secventa
			return NULL_TVALOARE;					/// cheia nu se afla in tabela
		else
			++i;
	}

	/// daca am parcurs toata secventa si 
	/// nu am gasit cheia returnam null
	return NULL_TVALOARE;
}


TValoare DO::sterge(TCheie c)
{
	/// <summary>
	/// Sterge perechea ce contine cheia data din dictionar
	/// Complexitate:
	/// 	In ipoteza SUH: cel mult (1/(1-a)) fara succes, (1/a * ln(1/(1-a))) cu succes
	///						a = factorul de incarcare al tabelei
	///						Daca a = constant -> Theta(1)
	///		Caz defavorabil: O(m)
	/// </summary>
	/// <param name="c"> Cheia corespunzatoare perechii ce se va sterge </param>
	/// <returns>
	/// Returneaza valoarea corespunzatoare cheii daca aceasta exista in dictionar /
	/// altfel NULL_TVALOARE
	/// </returns>

	int i = 0, j = 0;
	int val_de_returnat = NULL_TVALOARE;
	
	/// parcurge secventa de verificare
	while (i != m)
	{
		/// calculam urmatoarea pozitie de dispersie din secventa
		j = d(c, i);
		if (tabela[j].first == c)
		{
			/// daca am gasit cheia salvam valoare asociata ei
			val_de_returnat = tabela[j].second;
			
			/// marcam cheia ca fiind stearsa
			tabela[j].first = CHEIE_STEARSA;
			tabela[j].second = NULL_TVALOARE;
			nr--;

			/// returnam vechea valoare asociata cheii
			return val_de_returnat;
		}
		else if (tabela[j].first == NULL_TCHEIE)
		{
			/// daca am intalnit o cheie nula in secventa =>
			/// cheia nu exista in dictionar
			return NULL_TVALOARE;
		}
		else
			++i;
	}
	return NULL_TVALOARE;
}


void DO::inlocuiste(TCheie k, TValoare valoareVeche, TValoare valoareNoua)
{
	int i = 0;

	/// parcurgem toata secventa de verificare a cheii
	while (i != m)
	{
		/// calculam urmatoarea pozitie de dispersie din secventa
		int j = d(k, i);
		if (tabela[j].first == k)		/// daca am gasit cheia
		{
			if (tabela[j].second == valoareVeche) /// daca vechea valoare este egala cu cea data
				tabela[j].second = valoareNoua;	  /// actualizam valoarea
			return;								  /// incheiem executia
		}
		else if (tabela[j].first == NULL_TCHEIE)	/// daca am intalnit null in secventa
		{
			return;									/// incheiem executia
		}
		else
			++i;
	}
}


//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
//TValoare DO::sterge(TCheie c)
//{
//	int i = 0, j = 0;
//	int loc_de_sters = -1;
//	int val_de_returnat = NULL_TVALOARE;
//
//	while (i != m && loc_de_sters == -1)
//	{
//		j = d(c, i);
//		if (tabela[j].first == c)
//		{
//			loc_de_sters = j;
//			val_de_returnat = tabela[j].second;
//		}
//		else if (tabela[j].first == NULL_TCHEIE)
//		{
//			cout << c << " NU S-A STERS\n";
//			return NULL_TVALOARE;
//		}
//		else
//			++i;
//	}
//
//	if (loc_de_sters == -1)
//	{
//		//cout << c << " NU S-A GASIT\n";
//		return NULL_TVALOARE;
//	}
//
//	int curent = (i + 1) % m;
//	j = d(c, curent);
//	
//	while (curent != i && tabela[j].first != NULL_TCHEIE)
//	{
//		int p = d(tabela[j].first, 0);
//
//		if (loc_de_sters < j)
//		{
//			if (p <= loc_de_sters || p > j)
//			{
//				// mutare
//				tabela[loc_de_sters].first = tabela[j].first;
//				tabela[loc_de_sters].second = tabela[j].second;
//				loc_de_sters = j;
//			}
//		}
//		else if (loc_de_sters > j)
//		{
//			if (p <= loc_de_sters && p > j)
//			{
//				// mutare
//				tabela[loc_de_sters].first = tabela[j].first;
//				tabela[loc_de_sters].second = tabela[j].second;
//				loc_de_sters = j;
//			}
//		}
//
//		curent = (curent + 1) % m;
//		j = d(c, curent);
//	}
//
//
//	tabela[loc_de_sters].first = NULL_TCHEIE;
//	tabela[loc_de_sters].second = NULL_TVALOARE;
//	nr--;
//	return val_de_returnat;
//}


//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const
{
	/// <summary>
	/// Complexitate: Theta(1)
	/// Returneaza numarul de perechi din dictionar
	/// </summary>

	return nr;
}


//verifica daca dictionarul e vid
bool DO::vid() const
{
	/// <summary>
	/// Complexitate: Theta(1)
	/// Verifica daca exista perechi nenule in dictionar
	/// </summary>

	return nr == 0;
}


Iterator DO::iterator() const
{
	/// <summary>
	/// Returneaza un iterator pe dictionar
	/// Complexitate: Theta(1)
	/// </summary>

	return  Iterator(*this);
}


DO::~DO()
{
	/// <summary>
	/// Destructorul dictionarului ordonat
	/// Complexitate: Theta(1)
	/// </summary>

	/// eliberam spatiul ocupat de tabela din memorie
	delete[] tabela;
}