#ifndef __OpticalMat__
#define __OpticalMat__

#include "Material.h"
#include "cFCgraphics.h"
#include "TF1.h"
#include "TGraph.h"

class OpticalMat : public Material {
public:
	OpticalMat(std::string ="", Double_t =0, const std::vector<std::pair<float,float> >& = std::vector<std::pair<float,float> >(), TF1* =nullptr);
	~OpticalMat();

	void SetRefIndex(const std::vector<std::pair<float,float> >&); //pair(wavelength, ref index)
	std::vector<std::pair<float,float> >& GetRefIndex();

	void SetFitRefIndex(TF1*); //provide function to be fitted through TF1
	TF1* GetFitRefIndex(); //return TF1 pointer to fit function

	void DrawRefIndexPoints(); //draw points
	void DrawFitRefIndex(); //draw points and function

	void Print(std::string="save"); //define print for this class

private:
	// method with the fit function
	double FitRefIndex(double* x, double* par);

	// we need to store the refractive index characteristic of the material
	std::vector<std::pair<float,float> > RefIndex;
	float *lambda;
	float *n;
	
	// we need to store a TF1 pointer to the fit Ref Index function
	TF1* f;
	cFCgraphics* cFC;
	TGraph gr;
	TPad *pad;
};

#endif