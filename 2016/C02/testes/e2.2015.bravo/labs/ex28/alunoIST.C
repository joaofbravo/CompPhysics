#include "alunoIST.h"
#include <iostream>

using namespace std;

alunoIST::alunoIST(string n, unsigned int d, int numb, string br) : 
pessoa(n, d), number(numb), branch(br) {
	cout << __PRETTY_FUNCTION__ << endl;
}

alunoIST::~alunoIST() { cout << __PRETTY_FUNCTION__ << endl; }

void alunoIST::SetNumber(int numb){
	number = numb;
	cout << __PRETTY_FUNCTION__ << endl;
}

void alunoIST::SetBranch(string br){
	branch = br;
	cout << __PRETTY_FUNCTION__ << endl;
}

int alunoIST::GetNumber(){
	cout << __PRETTY_FUNCTION__ << endl;
	return number;
}

string alunoIST::GetBranch(){
	cout << __PRETTY_FUNCTION__ << endl;
	return branch;
}

void alunoIST::Print(){
	cout << GetName() << " was born in " << GetBornDate() << "." << endl;
	cout << "He/she is the number " << number << " of " << branch << "." << endl;
	cout << __PRETTY_FUNCTION__ << endl;
}