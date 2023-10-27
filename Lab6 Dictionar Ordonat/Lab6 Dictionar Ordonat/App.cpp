#include <iostream>
#include "DO.h"
#include "TestScurt.h"
#include "TestExtins.h"
#include <assert.h>

using namespace std;


///////////////////////////////////
bool descr2(TCheie c1, TCheie c2)
{
    if (c1 >= c2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
///////////////////////////////////

///////////////////////////////////
bool cresc2(TCheie c1, TCheie c2)
{
	if (c1 <= c2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
///////////////////////////////////


void test()
{
    DO a(cresc2);

    assert(a.vid() == true);
    a.adauga(79, 1);
    assert(a.vid() == false);
    assert(a.dim() == 1);
    a.adauga(63, 3);
    a.adauga(96, 1);
    assert(a.dim() == 3);
    a.adauga(14, 1);

    assert(a.adauga(14, 3) == 1);
    assert(a.adauga(14, 4) == 3);
    assert(a.adauga(14, 5) == 4);

    assert(a.dim() == 4);
    assert(a.cauta(14) == 5);
    assert(a.cauta(96) == 1);
    assert(a.cauta(63) == 3);

    a.adauga(15, 1);
    a.adauga(16, 1);
    a.adauga(17, 1);
    a.adauga(18, 1);
    a.adauga(19, 20);
    a.adauga(20, 1);
    a.adauga(21, 1);
    a.adauga(22, 1);
    a.adauga(23, 1);

    //a.afis();
    assert(a.sterge(19) == 20);
    //a.adauga(99, 10);
    //a.afis();

    Iterator it = a.iterator();
    assert(it.valid() == true);
    while (it.valid())
    {
        TElem el = it.element();
        //cout << "(" << el.first << ", " << el.second << "), ";
        it.urmator();
    }
    //cout << endl;

    a.inlocuiste(21, 2, 3);
    assert(a.cauta(21) == 1);

    a.inlocuiste(17, 1, 5);
    assert(a.cauta(17) == 5);

    a.inlocuiste(19, 2, 3);
    assert(a.cauta(19) == NULL_TVALOARE);

    a.inlocuiste(21, 1, 333);
    assert(a.cauta(21) == 333);

    assert(it.valid() == false);
    it.prim();
    assert(it.valid() == true);

    //a.afis();
}


int main()
{
    test();
    testAll();
    testAllExtins();
    cout << "Finished Tests!" << endl;
    return 0;
}