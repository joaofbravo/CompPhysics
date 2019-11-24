#ifndef __Material__
#define __Material__

#include "TROOT.h"
#include <string>

class Material {
public:
	Material(std::string ="", Double_t =0);
	virtual ~Material();

	std::string GetName();
	Double_t GetDensity();
	void SetName(std::string ="");
	void SetDensity(Double_t =0);
	virtual void Print();

protected:
	std::string name;
	Double_t density;
};

#endif
