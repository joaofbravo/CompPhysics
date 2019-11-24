#include "array2vec.h"
#include <iostream>

using namespace std;

int main(){
	//criar arrays
	int a1[6] = {1, 10, 5, 6, 9, 3};
	int a2[5] = {2, 5, 5, 7, 3};

	//copiar arrays para vector
	vector<int> *v1 = array2vecp(6, a1);
	vector<int> *v2 = array2vecp(5, a2);

	vector<int>::iterator vit;

	{
		for (vit = v1->begin(); vit != v1->end(); ++vit)
			cout << *vit << " ";
		cout << endl;

		for (vit = v2->begin(); vit != v2->end(); ++vit)
			cout << *vit << " ";
		cout << endl << endl;
	}

	//sort vector
	vec_sort(1, v1); //ordem crescente 
	vec_sort(-1, v2); //ordem decrescente

	{
		for (vit = v1->begin(); vit != v1->end(); ++vit)
			cout << *vit << " ";
		cout << endl;

		for (vit = v2->begin(); vit != v2->end(); ++vit)
			cout << *vit << " ";
		cout << endl << endl;
	}

	int a1_max = array2vecmax(6, a1);
	int a1_pos7 = array2vecfind(6, a1, 7);
	int a2_pos7 = array2vecfind(5, a2, 7);

	cout << "a1 Max: " << a1_max << endl;
	cout << "a1 7 position: " << a1_pos7 << endl;
	cout << "a2 7 position: " << a2_pos7 << endl;

	delete v1;
	delete v2;

	return 0;
}