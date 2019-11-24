#include "Turma.h"
#include <iostream>

using namespace std;

Turma::Turma(string name, int n) : va(new alunoIST* [n]), Tname(name), Nalunos(n) {
	cout << __PRETTY_FUNCTION__ << endl;
}

Turma::Turma(const Turma& pT) : va(new alunoIST* [pT.Nalunos]), Tname(pT.Tname), Nalunos(pT.Nalunos) {
	for (int i = 0; pT.va[i]!=NULL && i < Nalunos; ++i)
		va[i] = new alunoIST(pT.va[i]->GetName(), pT.va[i]->GetBornDate(), pT.va[i]->GetNumber(), pT.va[i]->GetBranch());

	cout << __PRETTY_FUNCTION__ << endl;
}

Turma::~Turma(){
	for (int i = 0; va[i]!=NULL && i < Nalunos; ++i)
		delete va[i];
	delete[] va;

	cout << __PRETTY_FUNCTION__ << endl;
}

const Turma& Turma::operator=(const Turma& T){
	if(this != &T){
		for (int i = 0; va[i]!=NULL && i < Nalunos; ++i)
			delete va[i];
		delete[] va;

		Tname = T.Tname;
		Nalunos = T.Nalunos;

		va = new alunoIST* [Nalunos];

		for (int i = 0; T.va[i]!=NULL && i < Nalunos; ++i)
			va[i] = new alunoIST(T.va[i]->GetName(), T.va[i]->GetBornDate(), T.va[i]->GetNumber(), T.va[i]->GetBranch());
	}
	
	cout << __PRETTY_FUNCTION__ << endl;

	return *this;
}

void Turma::AddAluno(alunoIST* const NewAluno){
	int i;

	for (i = 0; va[i]!=NULL && i < Nalunos; ++i);
		if(i == Nalunos){
			cout << "There is no space left in " << Tname << " for " << NewAluno->GetName() << "." << endl;
			return;
		}

	va[i] = NewAluno;

	cout << __PRETTY_FUNCTION__ << endl;
}

alunoIST* Turma::FindAluno(int numb){
	cout << __PRETTY_FUNCTION__ << endl;

	int i;

	// Correr array até ao último lugar vago
	for (i = 0; va[i]!=NULL && i < Nalunos; ++i);

	// Procura dicotómica
	int min = 0;
	int max = i - 1;

	while(min <= max) {
		int mid = (min+max) / 2;
		
		if (va[mid]->GetNumber() == numb)
			return va[mid];
		else if (va[mid]->GetNumber() > numb)
			max = mid - 1;
		else if (va[mid]->GetNumber() < numb)
			min = mid + 1;
	}

	// Se não existir esse aluno:
	cout << "Aluno " << numb << " is not in Turma " << Tname << "." << endl;
	return NULL;
}

void Turma::SetTname(string name){
	Tname = name;
	cout << __PRETTY_FUNCTION__ << endl;
}

string Turma::GetTname(){
	cout << __PRETTY_FUNCTION__ << endl;
	return Tname;
}

int Turma::GetNalunos(){
	cout << __PRETTY_FUNCTION__ << endl;
	return Nalunos;
}

void Turma::Print(int numb){
	switch(numb){
		case 0:
		cout << "Turma: " << Tname << endl;
		cout << "Nº Máx Alunos: " << Nalunos << endl;

		for (int i = 0; va[i]!=NULL && i < Nalunos; ++i)
			va[i]->Print();

		break;
		default:
		alunoIST* A = FindAluno(numb);

		if(A == NULL)
			break;

		A->Print();

		break;
	}

	cout << __PRETTY_FUNCTION__ << endl;
}