#include "classtestes.h"
#include <cstdio>
#include <cstdlib> //rand()
#include <ctime> //clock()
#include <cmath> //pow()
#include <vector>
#include <algorithm> //sort vector
#include <stack>

#define N 1000000

using namespace std;


int main(int argc, char *argv[]){

/*	//criar e imprimir matriz
	int m[4][5] = {
	 {0, 1, 2, 3, 4}, // row 0
	 {5, 6, 7, 8, 9}, // row 1
	 {10, 11, 12, 13, 14}, // row 2
	 {15, 16, 17, 18, 19} // last row
	};

	int *p = m[0];
	
	for(int i =0; i <20; i++){
		printf("%d ", *p);
		p++;
	}

	printf("\n");
*/

/*	//matrix 10x5 na heap
	int **m = new int*[10];

	for(int i=0; i<10; ++i){
		m[i]= new int[5];
	}

	for(int i=0; i<10; ++i){
		for(int j=0; j<5; ++j){
			m[i][j] = i*5 + j;

			cout << m[i][j] << " ";
		}

		cout << endl;
	}
*/

/*	//Vector: sort, print and get max
	vector<int> vec = {3, 1, 5, 2, 55, 3, 0, 8, 33, 12};

	sort(vec.begin(), vec.end()-2);

	vector<int>::iterator vecit = vec.begin();

	while (vecit!= vec.end()){
		cout << " value = " << *vecit << endl;
		vecit ++;
	}

	cout << *max_element(vec.begin(), vec.end()) << endl;

	vec.clear();
*/

/*	//Vector matrix 2x5
	vector<int> vcol(5, 69);
	vector< vector<int> > vrow(2,vcol);

	for(int i=0; i<vrow.size(); i++) {
		for (int j=0; j<vrow[i].size(); j++) {
			cout << vrow[i][j] << " ";
		}
		cout << endl;
	}
*/

/*	//Class testes
	point P(5,3);
	point Q = point(1,2);
	point *R = new point(4,4);
	cout << endl;

	point S = P;
	point T = P = Q;
	point& q = *R; //não chama o copy constructor
	point U = move(P);
	S = move(Q);
	cout << endl;

	*R = S + T;
	T += *R;
	S = -T;
	if (S == U)	cout << "---similar points!" << endl;
	if (S == -T)	cout << "---similar points!" << endl;
	cout << endl;

	delete R;
	cout << endl;
*/



	return 0;
}