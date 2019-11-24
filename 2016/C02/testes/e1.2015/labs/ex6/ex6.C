#include <iostream>
#include <cstdlib>

using namespace std;

#define recursive

int quadrado(const int&);


int main(){
	
	int x, result;

	cout << "Write a number: ";
	cin >> x;

	if(x<=0)
	{
		cout << "Write a positive integer." << endl;
		exit (-1);
	}

	result = quadrado(x);

	cout << result << endl;

	return 0;
}


#ifdef regular
int quadrado(const int &x){

	int result = 0.;

	for (int i = 0; i < x; ++i)
		result += x;

	return result;
}

#endif


#ifdef recursive
int quadrado(const int &x){

	static int result=0, i=0;

	if(i<x){
		i++;
		result = x + quadrado(x);
	}

	return result;
}

#endif