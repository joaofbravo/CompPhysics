#include "alunoIST.h"
#include <iostream>

int main(){

	alunoIST* a[3];

	a[0] = new alunoIST("João", 1997, 1, "MEFT");
	a[1] = new alunoIST("Filipe", 1996, 2, "MEFT");
	a[2] = new alunoIST();

	for (int i = 0; i < 3; ++i)
		a[i]->Print();

	a[2]->SetName("Zé");
	a[2]->SetBornDate(2000);
	a[2]->SetNumber(3);
	a[2]->SetBranch("MEEC");
	a[2]->Print();

	for (int i = 0; i < 3; ++i)
		delete a[i];

	cout << "//---------------------------------" << endl;

	pessoa* pTurma[3];
	pTurma[0] = new alunoIST("João", 1997, 1, "MEFT");
	pTurma[1] = new alunoIST("Filipe", 1996, 2, "MEFT");
	pTurma[2] = new alunoIST();

	Dummy(pTurma, 3);

	for (int i = 0; i < 3; ++i)
		delete pTurma[i];

	return 0;
}