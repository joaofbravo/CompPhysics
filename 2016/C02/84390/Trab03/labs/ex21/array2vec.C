#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> array2vec(const int n, const int* a){
	vector<int> vec(n);

	for (int i = 0; i < n; ++i)
		vec[i] = a[i];

	return vec;
}

vector<int>* array2vecp(const int n, const int* a){
	vector<int> *vec = new vector<int> (n);

	for (int i = 0; i < n; ++i)
		(*vec)[i] = a[i];

	return vec;
}

bool compare_greater(int i,int j) {return (i>j);}

void vec_sort(const int n, vector<int> *vec){

	switch(n){
		case 1:
		sort(vec->begin(), vec->end());

		break;
		case -1:
		sort(vec->begin(), vec->end(), compare_greater);

		break;
		default:
		cout << "Wrong argument for sorting" << endl;

		break;
	}
}

int array2vecmax(const int n, const int* a){
	vector<int> vec = array2vec(n, a);

	return *max_element(vec.begin(), vec.end());
}

int array2vecfind(const int n, const int* a, int value){
	vector<int> vec = array2vec(n, a);

	vector<int>::iterator vit = search_n(vec.begin(), vec.end(), 1, value);

	if (vit == vec.end()){
		cout << "Element " << value << " not found in array!" << endl;
		return -1;
	}

	return int(vit - vec.begin());
}