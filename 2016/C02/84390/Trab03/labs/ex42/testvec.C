#include "Vec.h"
#include "FCtools.h"
#include <iostream>
using namespace std;

int main() {

	//matrix 5x5
	double cm[][5] = {
		{1.0,   7.0,   5.0,    3.0,   -3.0 }, 
		{5.0,   2.0,   8.0,   -2.0,    4.0 },
		{1.0,  -5.0,  -4.0,    6.0,    7.6 },
		{0.0,  -5.0,   3.0,   +3.2,    3.3 },
		{1.0,   7.0,   2.0,    2.1,    1.2 }
	};

	//array of Vec’s for storing matrix rows
	Vec cv[5];

	//copy rows as arrays into Vecs
	for (int i=0; i<5; i++) 
		cv[i].SetEntries(5, cm[i]);

	FCtools tools;

	Vec* mat = tools.ReadFileToVecP("execs/matrix.txt", 5);

	//print both matrixes
	for (int i = 0; i < 5; ++i)
		cv[i].Print();	
	cout << endl << endl;

	for (int i = 0; i < 5; ++i)
		mat[i].Print();	
	cout << endl << endl;

	//testing the datamembers
	Vec A = mat[0];
	cout << "Printing A" << endl;
	A.Print();
	Vec B = mat[1];

	cout << "Printing B" << endl;
	B.Print();

	Vec C, D, E, F, G, H, I;
	double c[]={1.,2.};

	C = A + B;

	cout << "Printing C" << endl;
	C.Print();

	D = A*B;

	cout << "Printing D" << endl;
	D.Print();

	E = A-B;

	cout << "Printing E" << endl;
	E.Print();

	F = Vec(2,c);
	F.swap(0,1);

	cout << "Printing F" << endl;
	F.Print();
	
	G = A + F;

	cout << "Printing G" << endl;
	G.Print();

	double d = A.dot(B);
	cout << "d = " << d << endl;

	double n = !A;
	cout << "n= " << n << endl;

	H = A*2;

	cout << "Printing H" << endl;
	H.Print();

	I = 2*A;

	cout << "Printing I" << endl;
	I.Print();

	cout << endl << endl << "Print precision test:" << endl;

	double y[] = {1234567, 123456, 12345, 1234, 123, 12.12,
				  12.123, 12.1234, 12.12345, 12.123456,
				  1.1234567, 123.1234567};
	double z[] = {123.1234567, 1.1234567, 12.123456, 12.12345,
				  12.1234, 12.123, 12.12, 123, 1234.12, 12345,
				  123456, 1234567};
	Vec yy(12, y);
	Vec zz(12, z);
	yy.Print(7);
	zz.Print(7);

	return 0;
}