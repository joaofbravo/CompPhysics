#include "Mmap.h"

using namespace std;

int main(){
	
	map <string, vector< vector<int> > > Mmap;

	vector< vector<int> > a = GetMatrix(2, 3);
	vector< vector<int> > b = GetMatrix(3, 3);
	vector< vector<int> > c = GetMatrix(3, 2);

	a[0][0] = 2;
	a[1][0] = 3;
	a[0][1] = 10;
	a[1][1] = 2;
	a[0][2] = 5;
	a[1][2] = 7;

	b[0][0] = 5;
	b[1][0] = 10;
	b[2][0] = 15;
	b[0][1] = 1;
	b[1][1] = 1;
	b[2][1] = 1;
	b[0][2] = 3;
	b[1][2] = 5;
	b[2][2] = 4;

	c[0][0] = 5;
	c[1][0] = 10;
	c[2][0] = 15;
	c[0][1] = 1;
	c[1][1] = 2;
	c[2][1] = 1;

	Mmap["A"] = a;
	Mmap["B"] = b;
	Mmap["C"] = c;

	vector< vector<int> > d = Mmapfind(Mmap, "B");

	Mvecprint(a);
	Mvecprint(b);
	Mvecprint(c);
	Mvecprint(d);

	return 0;
}