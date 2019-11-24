#include "FCmatrixFull.h"
#include "FCmatrixBanded.h"

#include <iostream>

using namespace std;

int main()
{
	
	double d[][7] = { {1,4}, 
					{1,2,3},
			       	{1,2,3,6},
					{1,6,3,6,15},
					{1,2,3,2},
					{5,2,9},
					{1,5}};				

	
	vector<Vec> e(7);

	for (int i = 0; i < 7; ++i)
	{
		e[i] = Vec(5- abs(i-3));
		for (int j = 0; j < 5- abs(i-3); ++j)
			e[i][j] = d[i][j];
	}

	FCmatrixBanded E(e);
	E.Print();
	
	FCmatrixFull full(E);
	full.Print();
	E[0].Print();

}