#pragma once

typedef int TCheie;
typedef int TValoare;

#include <climits>
#define NULL_TVALOARE -1
#define NULL_TCHEIE -2147483647
#define CHEIE_STEARSA -2147483646

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

typedef bool(*Relatie)(TCheie, TCheie);

#include "Iterator.h"
class Iterator;


class DO
{

	friend class Iterator;
    
private:
	
	int m;				// capacitatea tabelei
	int nr;				// numarul de perechi din dictionar
	TElem* tabela;		// tabela
	Relatie rel;		// relatia dintre elemente
	int d(TCheie c, int i) const;	// functia de dispersie

	
	void rehash();
	int urm_prim(int num);

public:

	// constructorul implicit al dictionarului
	DO(Relatie r);

	// adauga o pereche (cheie, valoare) in dictionar
	// daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	////////////////////////////////////////
	void afis();
	///////////////////////////////////////

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	
	// inlocuieste valoarea mapata in prezent cheii k cu valoarea valoareNoua, dar numai in cazul in care valoarea curenta este egala cu valoareVeche. 
	// daca valoarea curenta nu este valoareVeche sau in cazul in care k nu este in cheie a dictionarului, dictionarul nu este modificat 
	void inlocuiste(TCheie k, TValoare valoareVeche, TValoare valoareNoua);


	//returneaza numarul de perechi (cheie, valoare) din dictionar
	int dim() const;

	//verifica daca dictionarul e vid
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	Iterator iterator() const;

	// destructorul dictionarului
	~DO();

};