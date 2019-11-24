#include "alunoIST.h"

void Dummy(pessoa** turma= NULL, const int count =0);

int main()
{
	pessoa** a = new pessoa*[5];

	for (int i = 0; i < 5; ++i)
		a[i]= new alunoIST(84390,"MEFT","Bravo",1997);
	
	Dummy(a, 5);

	delete [] *a;
	delete a;

	return 0;
}


void Dummy(pessoa** turma, const int count)
{	
	if(turma == NULL){
		cout << "No memory assigned!" << endl;
	}
	
	for (int i = 0; i < count; ++i)
		turma[i]->Print();
}