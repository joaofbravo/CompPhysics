#include "FCmatrixRotation.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;


FCmatrixRotation::FCmatrixRotation(double theta, double phi)
{
	double costheta = cos(theta);
	double sintheta = sin(theta);
	double cosphi = cos(phi);
	double sinphi = sin(phi);

	double ** mat = new double*[3];
	for (int i = 0; i < 3; ++i)
		mat[i] = new double[3];

	mat[0][0] = costheta*cosphi;
	mat[0][1] =	-sinphi;
	mat[0][2] = sintheta*cosphi;
	mat[1][0] = costheta*sinphi;
	mat[1][1] =	cosphi;
	mat[1][2] = sintheta*sinphi;
	mat[2][0] = -sintheta;
	mat[2][1] = 0;
	mat[2][2] = costheta;

	SetMatrix(mat,3,3);

	delete [] mat;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrixRotation::FCmatrixRotation (const TVector3& zaxis) : FCmatrixRotation(zaxis.Theta(),zaxis.Phi())
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCmatrixRotation::~FCmatrixRotation()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

TVector3 FCmatrixRotation::operator*(const TVector3& vec) const
{
	double ret0 = 0;
	double ret1 = 0;
	double ret2 = 0;

	for (int i = 0; i < 3; ++i)
	{
		ret0 += M[0][i]*vec[i];
		ret1 += M[1][i]*vec[i];
		ret2 += M[2][i]*vec[i];
	}

	TVector3 ret(ret0,ret1,ret2);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return ret;
}