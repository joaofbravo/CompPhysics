#include "atom.h"

using namespace std;

int main(){
	map<string, ATOM*> mperiodic;

	string name[6] ={"Hydrogen","Helium","Lithium","Beryllium","Boron","Carbon"};
	float A[6]= {1.01f,4.00f,6.94f,9.01f,10.81f,12.11f};

	// fill with 1st 6 elements
	for (int i = 0; i < 6; ++i){
		mperiodic.emplace(name[i], new ATOM());
		mperiodic[name[i]]->Z = i+1;
		mperiodic[name[i]]->A = A[i];
		mperiodic[name[i]]->mass = A[i] * 938.89f/1.01f; //MeV - natural units
	}

	// print the contents of every element
	print(mperiodic);

	for(int i=0; i<6; ++i)
		delete mperiodic[name[i]];

	return 0;
}