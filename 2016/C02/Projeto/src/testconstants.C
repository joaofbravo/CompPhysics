#include "ConstantsManager.h"
#include <iostream>

using namespace std;

int main()
{
	ConstantsManager a;
	ConstantsManager b("batatas");
	ConstantsManager c("couves");

	a.Print();
	cout <<endl;
	b.Print();
	cout <<endl;
	c.Print();
	
	return 0;
}