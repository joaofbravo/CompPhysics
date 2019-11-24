#include "pessoa.h"
#include <iostream>

using namespace std;

int main() {
	pessoa A("Filipe", 1996);
	string a_name = A.GetName();
	unsigned int a_datan = A.GetBornDate();
	A.Print();

	cout << "a_name: " << a_name << endl;
	cout << "a_datan: " << a_datan << endl;

	A.SetName("Joao");
	A.SetBornDate(1997);
	A.Print();

	cout << "//---------------------------------" << endl;

	pessoa P[10];
	pessoa** pTurma = DoArray(10, "Zé", 2000);

	for (int i = 0; i < 10; ++i)
		pTurma[i]->Print();

	for (int i = 0; i < 10; ++i)
		delete pTurma[i];

	delete[] pTurma;

	cout << "//-----------------" << endl;

	return 0;
}