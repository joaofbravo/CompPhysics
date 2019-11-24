#include "Motion1D.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

inline void swap(float* v, int j, int i)
{
	float c = v[j];
	v[j] = v[i];
	v[i] = c;
}

void selectsortarray(int n, float* v0, float* v1)
{
	int indmin;

	for (int i = 0; i < n-1; ++i) {
		indmin = i + 1;

		for(int j = indmin; j < n; j++) {
			if(v0[j] < v0[indmin])
				indmin = j;
		}

		if (v0[indmin] < v0[i]) {
			swap(v0,indmin,i);
			swap(v1,indmin,i);
		}
	}
}

Motion1D::Motion1D(int n) : N(n), t(new float [n]), x(new float [n]) {
	cout << __PRETTY_FUNCTION__ << endl;
}

Motion1D::~Motion1D(){
	delete[] t;
	delete[] x;

	cout << __PRETTY_FUNCTION__ << endl;
}

void Motion1D::SetMotion(int n, float* T, float* X)
{
	delete [] t;
	delete [] x;

	N = n;
	t = new float [n];
	x = new float [n];

	for(int i=0; i < n; i++)
	{
		t[i] = T[i];
		x[i] = X[i];
	}
	
	selectsortarray(N,t,x);

	cout << __PRETTY_FUNCTION__ << endl;
}

int Motion1D::GetN()
{
	cout << __PRETTY_FUNCTION__ << endl;
	return N;
}

float* Motion1D::GetTimes()
{
	float *T = new float [N];
	for (int i = 0; i < N; ++i)
		T[i] = t[i];

	cout << __PRETTY_FUNCTION__ << endl;
	return T;
}

float* Motion1D::GetPositions()
{
	float *X = new float [N];
	for (int i = 0; i < N; ++i)
		X[i] = t[i];

	cout << __PRETTY_FUNCTION__ << endl;
	return X;
}

void Motion1D::Print()
{
	cout << "Total Points: " << N << endl;

	for (int i = 0; i < N; ++i)
		cout << "Point[" << i << "]: t = " << t[i] << ",  x = " << x[i] << endl;

	cout << __PRETTY_FUNCTION__ << endl;
}

float Motion1D::TotalDistance(){
	float dist = 0.;

	for(int i= 1; i < N; ++i)
		dist += abs(x[i] - x[i-1]);

	cout << __PRETTY_FUNCTION__ << endl;
	return dist;
}

float Motion1D::MeanVelocity(){
	cout << __PRETTY_FUNCTION__ << endl;
	return TotalDistance() / (t[N-1] - t[0]);
}