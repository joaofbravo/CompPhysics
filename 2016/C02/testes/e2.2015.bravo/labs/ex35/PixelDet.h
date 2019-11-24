#ifndef __PixelDet__
#define __PixelDet__ 

#include "TROOT.h"
#include "TF1.h"
#include "TH2C.h"
#include "TRandom.h"
#include <vector>

typedef struct
{
	int success = 0;
  	float x = 0.;
  	float y = 0.;
  	int n = 0;
  	std::vector<int> pixels = std::vector<int>();
} event;

class PixelDet {
public:
	PixelDet(unsigned int = 100, unsigned int = 100, float = 500, float = 500); //dimentions of the grid
	PixelDet(std::vector<int>, unsigned int = 100, unsigned int = 100, float = 500, float = 500);
	~PixelDet();

	std::vector<int> EventNoise(float = 0.005);
	std::vector<int> EventSignal(float[2], unsigned int = 4, unsigned int = 4, unsigned int = 10); //Provide coords, dimentions of signal and signal
	
	TH2C DrawEvent(); // visualizar o acontecimento no detetor
	
	// Evt pode ser uma estrutura a definir no ficheiro .h
	// que reúna a informação da posição reconstruída do
	// evento e ainda quais os pixeis que estão associados
	event RecEvent(unsigned int = 4, unsigned int = 4, unsigned int = 10);

	void DumpEvent();
	
private:
	unsigned int n;
	unsigned int m;
	float xmax;
	float ymax;
	
	int** grid;
	TRandom rand;
	
	std::vector<int> GetSparse(int**, unsigned int = 100, unsigned int = 100);
	int** GetMatrix(std::vector<int>, unsigned int = 100, unsigned int = 100);
};

#endif
