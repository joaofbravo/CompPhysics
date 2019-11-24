#include "atom.h"
#include <iostream>

using namespace std;

void print(vector<ATOM*>& vec){

	vector<ATOM*>::iterator vit;

	for(vit = vec.begin(); vit != vec.end(); ++vit){	
		cout << "Name: " << (*vit)->name << endl;
		cout << "Atomic number: " << (*vit)->Z << endl;
		cout << "Mass number: " << (*vit)->A << endl;
		cout << "Mass: " << (*vit)->mass << " MeV" << endl << endl;
	}
}