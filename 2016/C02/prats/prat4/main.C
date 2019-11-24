#include "point1Dn.h"
#include <cstdio>

int main(){
	//local object
	{
		point1Dn P(50.);
		P.print();
	}

	point1Dn *a = NULL;
	{
		a = new point1Dn(2);
		a->print();
		(*a).SetX(3);
		a->print();
	}

	point1Dn Q(0.);
	Q.SetX(100.);
	Q.print();

	printf("It's the end..... %d !\n", (int)sizeof(Q));

	delete a;

	return 0;
}