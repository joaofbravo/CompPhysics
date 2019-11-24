#ifndef __ConstantsManager__
#define __ConstantsManager__

#include <string>
#include <fstream>

using std::string;
using std::ofstream;
using std::ifstream;

class ConstantsManager
{
public:
	ConstantsManager(string element = "Aluminium", string database = "data/constants.data");
	~ConstantsManager();
	void AddElement(string element);
	void SetElement(string element);
	void Print();

	//universal constants:
	double me;
	double Re;
	double Na;
	double alpha;
	double areamassa;

	//specific constants:
	double Z /*= 13*/;
	double A /*= 26.9815385*/;
	double P /*= 2.699*/;
	double X0/*= 2.699*/;
	double Rmech /*= 44.503*/;
	double C0 /*= -4.24*/;
	double a /*= 0.0802*/;
	double U0 /*= 0.1708*/;
	double U1 /*= 3.01*/;
	double m /*= 3.63*/;

private:
	ifstream IN;
	ofstream OUT;
};

#endif