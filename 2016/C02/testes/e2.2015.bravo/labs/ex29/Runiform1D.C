#include "Uniform1D.h"
#include <iostream>

using namespace std;

void FillFreeFall(int N, float* t, float *x, float t0=0, float tf=500, float x0=0, float v0x=0, float g=9.81);

int main() {
	// instantiate object Uniform1D
	Uniform1D *p1D = new Uniform1D(100, 0., 0., 1000., 10.);
	p1D->Print();
	cout << "//--------------------" << endl;

	Motion1D* pm[2] = {
		new Uniform1D(100, 0., 0., 500., 20.),
		new Motion1D(400)
	};

	float* x = new float [400];
	float* t = new float [400];
	cout << "//--------------------" << endl;
	
	FillFreeFall(400,t,x);
	pm[1]->SetMotion(400,t,x);
	cout << "//--------------------" << endl;

	pm[0]->Print();
	pm[1]->Print();
	cout << "//--------------------" << endl;

	Motion1D m[2] = {Motion1D(400), Motion1D(400)};
	cout << "//--------------------" << endl;

	FillFreeFall(400,t,x);
	m[0].SetMotion(400,t,x);
	cout << "//--------------------" << endl;

	FillFreeFall(400,t,x,0,500,0,1);
	m[1].SetMotion(400,t,x);
	cout << "//--------------------" << endl;

	m[0].Print();
	m[1].Print();
	cout << "//--------------------" << endl;

	delete p1D;
	delete pm[0];
	delete pm[1];
	delete x;
	delete t;
	cout << "//--------------------" << endl;

	return 0;
}

void FillFreeFall(int N, float* t, float *x, float t0, float tf, float x0, float v0x, float g)
{
	t[0] = t0;
	x[0] = x0;

	float tinc = (tf-t0) / ((float)N-1);

	for (int i = 1; i < N; ++i)
	{
		t[i] = t[i-1] + tinc;
		x[i] = x0 + v0x*t[i] - 0.5*g*t[i]*t[i];
	}

}