#ifndef __Func1D__
#define __Func1D__

class TF1;

class Func1D {

public:

	Func1D(const TF1* fp =nullptr);
	Func1D(const TF1&);
	Func1D(const Func1D&);

	virtual ~Func1D();

	void SetFunction(TF1&);

	double Evaluate(double)const;

	void Draw()const;

protected:
	TF1 *p;

};
#endif
