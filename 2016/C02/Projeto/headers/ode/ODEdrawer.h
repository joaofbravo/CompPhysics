#ifndef _ODEDRAWER__
#define _ODEDRAWER__

#include "ODEpoint.h"
#include "Spline3Interpolator.h"
#include "cFCgraphics.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TF1.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class ODEdrawer {
public:
	ODEdrawer();
	~ODEdrawer();

	void AddPad(const vector< vector<ODEpoint> >&, int x, int y, string ="Graph 1D;x;y", string ="AP", 
		const vector<Color_t>& =vector<Color_t>(), vector<TF1> =vector<TF1>(), const vector<Color_t>& =vector<Color_t>());
	
	void AddPad(const vector< vector<ODEpoint> >&, int x, int y, int z, string ="Graph 2D;x;y;z", string ="P0", 
		const vector<Color_t>& =vector<Color_t>());

	Spline3Interpolator GetSpline(const vector<ODEpoint>&, int x, int y);

	void Draw();
	void Print(string ="execs/ODE.pdf");

private:
	cFCgraphics C;
	vector<TGraph*> graph;
	vector<TGraph2D*> graph2d;

	static int padcounter;
};

#endif