#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

//Criar matriz mxn
vector< vector<int>* >* GetMatrix(int mrows, int ncols, int val){

	vector< vector<int>* > *mx = new vector< vector<int>* > (mrows);

	for (int i = 0; i < mrows; ++i)
		(*mx)[i] = new vector<int> (ncols, val);

	return mx;
}

//Retornar matriz da chave "key"
vector< vector<int>* >* Mmapfind(map <string, vector< vector<int>* >* > &Mmap, string key){
	if(Mmap.find(key) == Mmap.end()){
		cout << "Matrix " << key << " doesn't exist!" << endl;
		exit(-1);
	}

	return Mmap.find(key)->second;
}

//Print da matriz mxn vector
void Mvecprint(vector< vector<int>* > *mx){

	for (unsigned int i = 0; i < mx->size(); ++i){
		for (unsigned int j = 0; j < (*mx)[i]->size(); ++j){
			cout << (*((*mx)[i]))[j] << " ";
			//Debug: cout << i << " " << j << " " << mx[0][i][0][j] << " " << &mx[0][i][0][j] << " ";
		}

		cout << endl;
	}

	cout << endl;
}

//Apagar matrizes vector
void Mvecdelete(vector< vector<int>* > *mx){

	for(unsigned int i = 0; i < mx->size(); ++i)
		delete (*mx)[i];

	delete mx;
}