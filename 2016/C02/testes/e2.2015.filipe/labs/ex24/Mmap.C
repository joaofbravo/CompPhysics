#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

//Criar matriz mxn
vector< vector<int> > GetMatrix(int mrows, int ncols, int val){

	vector<int> vcol(ncols, val);
	vector< vector<int> > mx(mrows, vcol);

	return mx;
}

//Retornar matriz da chave "key"
vector< vector<int> >& Mmapfind(map <string, vector< vector<int> > > &Mmap, string key){
	if(Mmap.find(key) == Mmap.end()){
		cout << "Matrix " << key << " doesn't exist!" << endl;
		exit(-1);
	}

	return Mmap.find(key)->second;
}

//Print da matriz mxn vector
void Mvecprint(vector< vector<int> > &mx){

	for (unsigned int i = 0; i < mx.size(); ++i){
		for (unsigned int j = 0; j < mx[i].size(); ++j)
			cout << mx[i][j] << " ";

		cout << endl;
	}

	cout << endl;
}