#include "atom.h"

using namespace std;

int main(){
	vector<ATOM*> vperiodic(6);

	string name[6] ={"Hydrogen","Helium","Lithium","Beryllium","Boron","Carbon"};
	float A[6]= {1.01f,4.00f,6.94f,9.01f,10.81f,12.11f};

	// fill with 1st 6 elements
	for (int i = 0; i < 6; ++i){
		vperiodic[i] = new ATOM;
		vperiodic[i]->name = name[i];
		vperiodic[i]->Z = i+1;
		vperiodic[i]->A = A[i];
		vperiodic[i]->mass = A[i] * 938.89f/1.01f; //MeV - natural units
	}
	
	// print the contents of every element
	print(vperiodic);

	for (int i=0; i<6; ++i)
		delete vperiodic[i];

	return 0;
}