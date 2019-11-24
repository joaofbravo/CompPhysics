#include "Turma.h"
#include <iostream>

using namespace std;

int main(){
	Turma T21("MEFT T21", 5);
	cout << "//--------------------" << endl;

	Turma T22(T21);
	cout << "//--------------------" << endl;

	Turma T23;
	cout << "//--------------------" << endl;

	alunoIST* A1 = new alunoIST("João", 1997, 84400, "MEFT");
	alunoIST* A2 = new alunoIST("Filipe", 1996, 84401, "MEFT");
	alunoIST* A3 = new alunoIST("Zé3", 2000, 84402, "MEEC");
	alunoIST* A4 = new alunoIST("Zé4", 2001, 84403, "MEEC");
	alunoIST* A5 = new alunoIST("Zé5", 2002, 84404, "MEEC");
	alunoIST* A6 = new alunoIST("Zé6", 2003, 84405, "MEEC");
	cout << "//--------------------" << endl;

	T21.AddAluno(A1);  cout << "//--------------------" << endl;
	T21.AddAluno(A2);  cout << "//--------------------" << endl;
	T21.AddAluno(A3);  cout << "//--------------------" << endl;
	T21.AddAluno(A4);  cout << "//--------------------" << endl;
	T21.AddAluno(A5);  cout << "//--------------------" << endl;
	T21.AddAluno(A6);  cout << "//--------------------" << endl;
	T23.AddAluno(A6);  cout << "//--------------------" << endl;

	T23 = T21;  cout << "//--------------------" << endl;

	T22.SetTname("MEBIOM");  cout << "//--------------------" << endl;
	T23.SetTname("T23");  cout << "//--------------------" << endl;

	cout << "T22 Nome: " << T22.GetTname() << endl;
	cout << "T22 Nalunos máx: " << T22.GetNalunos() << endl;
	cout << "//--------------------" << endl;

	alunoIST* B1 = T21.FindAluno(84401);
	cout << "//--------------------" << endl;
	alunoIST* B2 = T21.FindAluno(84403);
	cout << "//--------------------" << endl;
	// B3 não é usado porque é NULL
	alunoIST* B3 = T21.FindAluno(10000);
	cout << "//--------------------" << endl;

	B1->Print();  cout << "//--------------------" << endl;
	B2->Print();  cout << "//--------------------" << endl;
	
	T21.Print();  cout << "//--------------------" << endl;
	T22.Print();  cout << "//--------------------" << endl;
	T23.Print();  cout << "//--------------------" << endl;
	T21.Print(84401);  cout << "//--------------------" << endl;
	T23.Print(10000);  cout << "//--------------------" << endl;

	return 0;
}