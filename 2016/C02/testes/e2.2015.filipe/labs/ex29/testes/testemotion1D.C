#include "../Motion1D.h"
#include <iostream>

using namespace std;

int main()
{
	Motion1D traj;
	cout << "//--------------------" << endl;
	
	float x[] = {2.,3.,4.,5.};
	float t[] = {0.,5.,4.,3.};
	
	traj.SetMotion(4,t,x);
	
	cout << "N = " << traj.GetN() << endl;

	float* t1 =traj.GetTimes();
	float* x1 =traj.GetPositions();

	cout << "//--------------------" << endl;

	for (int i = 0; i < traj.GetN(); ++i)
		cout << "Point[" << i << "]: t = " << t1[i] << "; x = " << x1[i] << ";" << endl;
	cout << "//--------------------" << endl;
	
	traj.Print();
	cout << "//--------------------" << endl;

	cout << "Dist = " << traj.TotalDistance() << endl;
	cout << "//--------------------" << endl;
	
	cout << "MeanVelocity = " << traj.MeanVelocity() << endl;
	cout << "//--------------------" << endl;
}