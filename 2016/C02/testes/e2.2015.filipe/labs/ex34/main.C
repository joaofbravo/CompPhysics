#include "OpticalMat.h"

using namespace std;

int main()
{	
	cout << "Hi!"<< endl;
	pair<float,float> point[4];
	vector<pair<float,float> > coord (4);
	float lambda[4]={686.7, 589.3, 527.0, 396.8};
	float ref[4] = {2.40735, 2.41734, 2.42694, 2.46476};

	cout << "Hi!"<< endl;

	for (int i = 0; i < 4; ++i)
	{
		point[i].first = lambda[i];
		point[i].second = ref[i];
		coord[i] = point[i];
	}
	
	OpticalMat A("Diamante", 3500, coord);
	
	//testing
	A.SetRefIndex(A.GetRefIndex()); 

	TF1* f = A.GetFitRefIndex();

	A.SetFitRefIndex(f);

	delete f;

	//Implementing
	A.DrawRefIndexPoints();
	A.DrawFitRefIndex();
	
	A.DrawRefIndexPoints();
	A.DrawFitRefIndex();
 
	A.DrawFitRefIndex();
	
	A.Print();
	
	return 0;
}