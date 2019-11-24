#include "ODEpoint.h"
#include "ODEsolver.h"
#include "ODEdrawer.h"
#include "Spline3Interpolator.h"
#include "Func1D.h"

using namespace std;

int main()
{
	double step = 0.01;
	double MaxTime = 60.; //seconds

	//t = x[0]; y = x[1]; v = x[2]
	//g = [0]

	//dy/dt = v
	//dv/dt = -g-b/m*v^2

	vector<TFormula> v;
	v.push_back(TFormula("1","x[2]"));
	v.push_back(TFormula("2","-9.8 - 0.0085*x[2]*x[2]*x[2]/TMath::Abs(x[2])"));

	ODEsolver solver;
	solver.SetODEfunc(v);

	ODEpoint ini(3);
	ini[0] = 0.001;
	ini[1] = 1500.;
	ini[2] = 0.001;

	vector<ODEpoint> points = solver.RK4(ini, step, MaxTime);
	
	ODEdrawer a;
	Spline3Interpolator y_t_spline(a.GetSpline(points, 0, 1)); // y em funçao de t
	Func1D fpos(y_t_spline.GetInterpolationFunction());
	fpos.Draw("y(t);t (s);y (m)","QuedaLivre.pdf");

	double t = 0.;
	while(fpos.Eval(t)>0 && t<MaxTime)
		t += (step*0.1);

	if (t>MaxTime)
	{
		cout << "Did not hit the ground! It needs more time." << endl;
		return -1;
	}
	else
		cout << "\n\nTime to hit the ground: "<< t << " s" << endl << endl;

	return 0;	
}