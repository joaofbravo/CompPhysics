#include "pessoa.h"
#include <iostream>

using namespace std;

pessoa::pessoa(string n, unsigned int d) : name(n), DataN(d) {
	cout << __PRETTY_FUNCTION__ << endl;
}

pessoa::~pessoa(){ cout << __PRETTY_FUNCTION__ << endl;}

void pessoa::SetName(string n){
	name = n;
	cout << __PRETTY_FUNCTION__ << endl;
}

void pessoa::SetBornDate(unsigned int d){
	DataN = d;
	cout << __PRETTY_FUNCTION__ << endl;
}

string pessoa::GetName(){
	cout << __PRETTY_FUNCTION__ << endl;
	return name;
}

unsigned int pessoa::GetBornDate(){
	cout << __PRETTY_FUNCTION__ << endl;
	return DataN;
}

void pessoa::Print(){
	cout << __PRETTY_FUNCTION__ << endl;
	cout << name << " was born in " << DataN << "." << endl;
}


pessoa** DoArray(int N, string n, unsigned int d){

	cout << __PRETTY_FUNCTION__ << endl;

	pessoa **P = new pessoa* [N];
	for (int i = 0; i < N; ++i)
		P[i] = new pessoa (n, d);

	return P;
}

void Dummy(pessoa** p, const int N){
	if(p == NULL){
		cout << "No memory assigned!" << endl;
	}
	
	for (int i = 0; i < N; ++i)
		p[i]->Print();
}