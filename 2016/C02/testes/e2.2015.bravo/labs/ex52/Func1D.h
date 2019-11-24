#ifndef __Func1D__
#define __Func1D__

#include "TF1.h"
#include <string>

using std::string;

class Func1D {
public:
	Func1D(const TF1* =nullptr);
	Func1D(const TF1&);
	Func1D(const Func1D&);
	Func1D(Func1D&&);
	virtual ~Func1D();

	// assignments
	const Func1D& operator= (const Func1D&);
	Func1D& operator= (Func1D&&);

	// other
	void SetFunction(TF1&);
	TF1 GetFunction() const;

	double Eval(double) const;

	void Draw(string title ="", string print = "") const;

protected:
	TF1* F;
};

#endif