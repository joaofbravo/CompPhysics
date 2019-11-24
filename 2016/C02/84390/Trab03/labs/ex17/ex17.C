#include <iostream>
#include <ctime>

using namespace std;

int* func1();

int& func2();


int main(){
	
	srand(time(NULL));

	int *x1 = func1();
	int &x2 = func2(); //tenho que inicializar sempre as referencias

	for (int i = 0; i < 1000000; ++i){
		x1 = func1();
		int &x3 = func2(); //não posso reinicializar &x2 porque shadows o primeiro
	}

	cout << "*x1 = " << *x1 << endl;
	cout << "x1: " << x1 << endl;
	cout << "\nx2 = " << x2 << endl;
	cout << "&x2: " << &x2 << endl;

	delete x1;
	delete &x2;
	
	return 0;
}


int* func1(){
	int *x1 = new int;
	*x1 = rand();

//	cout << "func1 address: " << x1 << endl;

	return x1;
}


int& func2(){
	int *x2 = new int;
	*x2 = rand();

//	cout << "func2 address: " << x2 << endl << endl;

	return *x2;
}