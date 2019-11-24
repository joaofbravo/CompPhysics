#include <iostream>

using namespace std;

double fact(int);

int main()
{
	int n=0;

	cout << "Introduza um número inteiro não negativo: ";
	cin >> n;

	if(n<0){
		cout << "Introduza um número inteiro não negativo" << endl;
		return -1;
	}

	cout << n <<"! = " << fact(n) << endl;
}

double fact(int n)
{
	if (n==0)
		return 1;
	
	return n * fact(n-1);
}