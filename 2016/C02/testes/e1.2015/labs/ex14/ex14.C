#include "fvector.h"

int main(){

	// retornar uma matriz de inteiros de dimensão 100x50 inicializados a 1
	int ***a = fintv(100, 50);
	
	// retornar um tensor de double de dimensão 100x50x20 inicializados a 5.
	double ***b = fdoublev(100, 50, 20);
	double ***c = fdoublev(100, 50);

	print(a, 100, 50);
	print(b, 100, 50, 20);
	print(c, 100, 50);

    deletev(a, 100, 50);
    deletev(b, 100, 50);
    deletev(c, 100, 50);

	return 0;
}