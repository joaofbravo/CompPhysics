#include <string>

#ifndef __Turma__
#define __Turma__

#include "alunoIST.h"

using namespace std;

class Turma {
public:
	Turma(string="None", int=1); //nome da turma, num de alunos
	Turma(const Turma&);
	~Turma();

	const Turma& operator=(const Turma&);
	void AddAluno(alunoIST* const);
	alunoIST* FindAluno(int);
	void SetTname(string);
	string GetTname();
	int GetNalunos();
	void Print(int=0);	

private:
	alunoIST **va; //pointer to array de pointers de objetos
	string Tname;
	int Nalunos;
};

#endif