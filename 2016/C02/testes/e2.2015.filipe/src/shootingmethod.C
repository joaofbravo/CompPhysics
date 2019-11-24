#include "ODEsolver.h"
#include "ODEdrawer.h"
#include "ZeroFinder.h"
#include "TF1.h"
#include <cmath>
#include <limits>

using namespace std;

ODEsolver solver;
// vector<ODEpoint> points;
double shoot(double* var, double* par);


int main()
{
	vector<TFormula> v;
	double Target = 300;
	double velocity = 2000;
	double step = 0.01;
	double MaxTime = 40;
	double b = 1;
	double m = 100;
	double g = 9.8;

	//t=x[0] x = x[1]; vx = x[2]; y = x[3]; vy = x[4]
	//b = [0]; m = [1]; g = [2]
	v.push_back(TFormula("1","x[2]"));
	v.push_back(TFormula("2","-[0]/[1]*x[2]*sqrt(x[2]*x[2] + x[4]*x[4])"));
	v.push_back(TFormula("3","x[4]"));
	v.push_back(TFormula("4","-[2] -[0]/[1]*x[4]*sqrt(x[2]*x[2] + x[4]*x[4])"));

	double fpar[3] = {b,m,g};
	solver.SetODEfunc(v);
	solver.SetPar(fpar);

	TF1 target("target",shoot,0,M_PI/2.,4);
	double rootspar[4] = {velocity,step,MaxTime,Target};
	target.SetParameters(rootspar);


	ZeroFinder z(target);

	double teta = z.Secant(30*M_PI/180.,70*M_PI/180.,0.0001,100);


	if (teta==0)
	{
		cout << "\n\n\n\nMethod didn't converge!!!" << endl;
		return -1;
	}

	else
		cout << "\n\n\n\nWe got a hit!!!! teta = " << teta*180/M_PI << "º\n\n\n\n" << endl;

	ODEdrawer a;

	double ainit[] = {0,0,velocity*cos(teta),0,velocity*sin(teta)};
	ODEpoint ini(5,ainit);

	vector < vector <ODEpoint> > point;
	vector<ODEpoint> points (solver.RK4(ini,step*0.1,MaxTime));
	vector<ODEpoint> corrected;

	for (int i = 0; points[i][3] >= 0 && i < points.size(); ++i)
		corrected.push_back(points[i]);

	
	point.push_back(corrected);
	
	a.AddPad(point,1,3,"Canon Shooting;x(m);y(m)");
	a.Draw();

	return 0;
}

//if method fails return 0
//pars: [0] = |v0|; [1] = h; [2] = Tf; [3] = target;
//var: angle of shooting

double shoot(double* var, double* par)
{
	double ainit[] = {0,0,par[0]*cos(var[0]),0,par[0]*sin(var[0])};
	ODEpoint ini(5,ainit);
	vector<ODEpoint> points = solver.RK4(ini,par[1],par[2]);

	int i;

	for (i = 1; points[i][3] > 0 && i < points.size(); ++i);
		// points[i].Print(10,10);
	
	if(i == points.size())
	{
		cout << "Method did not converge for unkown reasons, returning NaN\n\n" <<endl;
		return std::numeric_limits<double>::quiet_NaN();
	}	
	i--;
	// cout << "hi\n\n\n\n\n\n\n\n";

	

	if(points[i+1][3] > 0)
	{
		cout << "Method did not converge, please add more time, returning NaN\n\n" <<endl;
		return std::numeric_limits<double>::quiet_NaN();
	}

	else
	{
		cout <<"teta: "<< var[0] <<" distance from target: " << points[i][1] - par[3] << endl;
		return points[i][1] - par[3];
	}

}