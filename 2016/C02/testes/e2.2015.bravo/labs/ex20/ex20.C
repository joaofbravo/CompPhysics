#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

vector<double> rand2vec(int n);
vector<double>* rand2vecp(int n);


int main(){
	
	srand(time(NULL));

	vector<double> x1 = rand2vec(10);
	vector<double> *x2 = rand2vecp(15);
	vector<double>::iterator vit;

	for (vit=x1.begin(); vit!=x1.end(); ++vit){
		cout << *vit << " ";
	}
	cout << endl;

	for (vit=x2->begin(); vit!=x2->end(); ++vit){
		cout << *vit << " ";
	}
	cout << endl;

	delete x2;
	
	return 0;
}


vector<double> rand2vec(int n){
	vector<double> x(n);

	for (int i = 0; i < n; ++i){
		x[i] = ((double)rand() / (double)RAND_MAX) * 360;
	}

	return x;
}

vector<double>* rand2vecp(int n){
	vector<double> *x = new vector<double> (n);

	for (int i = 0; i < n; ++i){
		(*x)[i] = ((double)rand() / (double)RAND_MAX) * 360;
	}

	return x;
}