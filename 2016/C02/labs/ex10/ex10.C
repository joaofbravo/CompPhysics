#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

float rdm(float min=5, float max=55);
float avg(vector<float>&, vector<float>::iterator&);
float desv(vector<float>&, vector<float>::iterator&, float&);


int main()
{
	srand(time(NULL));

	cout << "This program calculates the average and standard deviation of y=x/(x-10) for 1000 randomly generated values between 5 and 55.\n" << endl;

	vector<float> vf;
	float x=0.;

	for(int i=0; i<1000;i++)
		{
			x=rdm();
			vf.push_back(x/(x-10));
		}

	float mf=0.;
	float df=0.;	
	vector<float>::iterator vit;

	mf = avg(vf, vit);
	df = desv(vf, vit, mf);

	cout << "\nThe average is " << mf << " and the standard deviation is " << df << endl << endl;		

	return 0;
}


float rdm(float min, float max)
{
	float b = ((float)rand()/((float)RAND_MAX))*(max-min) +min;

	cout << b << endl;

	return b;
}


float avg(vector<float>& v, vector<float>::iterator &vit)
{
	float m = 0.;
	int i = 1;
	
	for(vit=v.begin(), i=0; vit<v.end(); vit++, i++)
		m += *vit;
	
	return (m /= (float)i);
}


float desv(vector<float>& v, vector<float>::iterator &vit, float& m)
{
	float d = 0.;
	int i = 0;

	for(vit=v.begin(), i=-1; vit<v.end(); vit++, i++)
		d += (*vit-m) * (*vit-m);
	
	d /= (float)i;

	return sqrt(d);
}
