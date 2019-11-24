#ifndef __MYFORMULA__
#define __MYFORMULA__

#include <string>
#include "TFormula.h"

using std::string;

class MyFormula : public TFormula{
public:
	MyFormula(string ="");
	~MyFormula();

	void SetFormula(string ="");
	void DrawAndSave(double =0., double =1.);

private:
	TFormula F;
	static int fcounter;
	string expression;
};

#endif