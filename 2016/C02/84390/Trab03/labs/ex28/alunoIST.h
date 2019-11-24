#ifndef __alunoIST__
#define __alunoIST__

#include "pessoa.h"

using namespace std;

class alunoIST : public pessoa {
public:
	//constructor (nome do aluno, data de nascimento, numero, curso)
	alunoIST(string="Nobody", unsigned int=0, int=0, string="None");
	~alunoIST();

	void SetNumber(int);
	void SetBranch(string);
	int GetNumber();
	string GetBranch();
	void Print();
	 
private:
	int number;
	string branch;
};

#endif