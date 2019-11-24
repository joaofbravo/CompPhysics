#include "FCtools.h"
#include "Vec.h"
#include "FCmatrixFull.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {

	FCtools tools;

	vector<string> lines = tools.ReadFileToString("execs/matrix.txt");

	cout << "Test vector<string>:" << endl;
	for (vector<string>::iterator i = lines.begin(); i != lines.end(); ++i)
		cout << *i << endl;
	cout << endl;


	vector<Vec> lines2 = tools.ReadFileToVecVector("execs/matrix.txt");

	cout << "Test vector<Vec>:" << endl;
	for (vector<Vec>::iterator i = lines2.begin(); i != lines2.end(); ++i)
		(*i).Print();
	cout << endl;


	Vec longline = tools.ReadFileToVec("execs/matrix.txt");

	cout << "Test Vec:" << endl;
	longline.Print();
	cout << endl;


	Vec* mat = tools.ReadFileToVecP("execs/matrix.txt", 5);

	cout << "Test Vec*:" << endl;
	for (int i = 0; i < 5; ++i)
		mat[i].Print();	
	cout << endl;


	FCmatrixFull M = tools.ReadFileToMatrix("execs/matrix.txt");

	cout << "Test FCmatrixFull:" << endl;
	M.Print();

	return 0;
}