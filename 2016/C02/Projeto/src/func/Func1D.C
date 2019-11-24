#include "Func1D.h"
#include "TF1.h"
#include "cFCgraphics.h"

using namespace std;

Func1D::Func1D(TF1* fp)
{
	if(fp)
		F = fp;
	else
		F = nullptr;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Func1D::Func1D(TF1& fp)
{
	F = &fp;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Func1D::Func1D(Func1D& f)
{
	if(f.F)
		F = f.F;
	else
		F = nullptr;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Func1D::Func1D(Func1D&& f)
{
	if(f.F){
		F = f.F;
		f.F = nullptr;
	}
	else
		F = nullptr;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Func1D::~Func1D()
{
	// if(F) delete F;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

//=============== assignments ===============

const Func1D& Func1D::operator= (Func1D& f) {
	if(this != &f){
		if(f.F)
			F = f.F;
		else
			F = nullptr;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

Func1D& Func1D::operator= (Func1D&& f) {
	if (F) delete F;

	if(f.F){
		F = f.F;
		f.F = nullptr;
	}
	else
		F = nullptr;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

//=============== other methods ===============

void Func1D::SetFunction(TF1& fp)
{

	F = &fp;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

TF1 Func1D::GetFunction() const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	if (!F){
		cout << __PRETTY_FUNCTION__ << ": ATTENTION! No function added, returning 0." << endl;
		return TF1();
	}

	return *F;
}

double Func1D::Eval(double x) const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	if(!F) {
		cout << __PRETTY_FUNCTION__ << ": ATTENTION! No function added, returning 0." << endl;
		return 0.;
	}

	return F->Eval(x);
}

void Func1D::Draw(string name, string print) const
{
	if(F)
	{
		cFCgraphics G;

		string title;

		if(name.empty())
		{
			title = "Function: ";
			string formula = (string) F->GetExpFormula();
			if(formula.empty())
				title += "User-defined";
			else
				title += formula;
			title += ";x;y";
		}
		else
			title=name;

		F->SetTitle(title.c_str());

		TPad *pad1 = G.CreatePad("pad1");
		G.AddObject(F,"pad1");
		G.AddObject(pad1);

		G.Draw();
		if(!print.empty())
			G.Print(print);
	}
	else
		cout <<__PRETTY_FUNCTION__<< ": ATENTION! No function added, will not be drawing anything."<<endl;
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}