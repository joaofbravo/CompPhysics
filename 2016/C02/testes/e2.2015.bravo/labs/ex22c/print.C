#include "atom.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void print(map<string,ATOM*> &m){
	string el;

	cout << "Wich element would you like to find? ";
	cin >> el;

	if (el == "all" || el == "All"){
		
		map<string,ATOM*>::iterator mit;

		for(mit = m.begin(); mit != m.end(); ++mit){	
			cout << "Name: " << mit->first << endl;
			cout << "Atomic number: " << mit->second->Z << endl;
			cout << "Mass number: " << mit->second->A << endl;
			cout << "Mass: " << mit->second->mass << " MeV" << endl << endl;
		}

	} else {
		
		if(m.find(el) == m.end()){
			cout << el << " doesn't exist!" << endl;
			exit(-1);
		}

		ATOM *el_info = m.find(el)->second;

		cout << "Name: " << el << endl;
		cout << "Atomic number: " << el_info->Z << endl;
		cout << "Mass number: " << el_info->A << endl;
		cout << "Mass: " << el_info->mass << " MeV" << endl << endl;
	}
}