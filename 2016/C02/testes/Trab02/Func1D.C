#include "Func1D.h"
#include "TF1.h"
#include "cFCgraphics.h"

using namespace std;

Func1D::Func1D(const TF1 * fp)
{
	p= nullptr;
	if(fp)
		p=new TF1 (*fp);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Func1D::Func1D(const TF1 &fp)
{
	p=new TF1 (fp);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Func1D::Func1D(const Func1D& f)
{
	p= nullptr;
	
	if(f.p)
		p=new TF1 (*(f.p));

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Func1D::~Func1D()
{
	if(p)delete p;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

void Func1D::SetFunction(TF1& fp)
{
	if(p) delete p;

	p=new TF1 (fp);
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Func1D::Draw() const
{
	if(p)
	{
		cFCgraphics G;

		string title = "Function: ";
		string formula = (string) p->GetExpFormula();
		if(formula.empty())	
			title += "Derivative";
		else
			title += formula;
		title += ";x;y";

		p->SetTitle(title.c_str());

		TPad *pad1 = G.CreatePad("pad1");
		G.AddObject(p,"pad1");
		G.AddObject(pad1);

		G.Draw();
	}

	else
		cout <<__PRETTY_FUNCTION__<< ": ATENTION! No function added, will not drawing anything."<<endl;
	

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

double Func1D::Evaluate(double x) const
{
	if(p)
	{
		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif
		return p->Eval(x);
	}
	else
	{		
		cout <<__PRETTY_FUNCTION__<< ": ATENTION! No function added, returning 0."<<endl;
		
		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return 0;
	}
}