#include "PixelDet.h"
#include <ctime>
#include <iostream>

using namespace std;

PixelDet::PixelDet(unsigned int N, unsigned int M, float x, float y) : n(N), m(M), xmax(x), ymax(y)
{
	grid = new int*[N];

	for (int i = 0; i < N; ++i)
		grid[i]= new int [M];
	
	rand = TRandom(time(nullptr));

	cout << __PRETTY_FUNCTION__ << endl;
}

PixelDet::PixelDet(std::vector<int> sparse, unsigned int N, unsigned int M, float x, float y) : n(N), m(M), xmax(x), ymax(y)
{
	grid = GetMatrix(sparse, N, M);
	
	rand = TRandom(time(nullptr));

	cout << __PRETTY_FUNCTION__ << endl;
}

PixelDet::~PixelDet()
{
	for (int i = 0; i < n; ++i)
		delete [] grid[i];
	delete [] grid;
	
	cout << __PRETTY_FUNCTION__ << endl;
}

vector<int> PixelDet::EventNoise(float prob)
{
	for (int i = 0; i < n; ++i)
	{
		Double_t* array = new Double_t[m];

		rand.RndmArray(m,array);

		for (int j = 0; j < m; ++j){
			if(array[j]<prob)
				grid[i][j]=1;
			else
				grid[i][j]=0;		
		}

		delete [] array;
	}	
	cout << __PRETTY_FUNCTION__ << endl;

	return GetSparse(grid);
}

vector<int> PixelDet::EventSignal(float a[2], unsigned int N, unsigned int M, unsigned int signal)
{
	//Generate positions of the perturbed pixels
	unsigned int dim = N*M;
	Double_t prob = (double)signal/(double)(dim);

	Double_t* rdsarray = new Double_t[m];
	int* posarray = new int [N*M] {0};
	
	rand.RndmArray(dim,rdsarray);
	
	for (int i = 0; i < N*M; ++i){
		if(rdsarray[i]<prob)
			posarray[i]=1;
	}

	while(1)
	{
		int sum = 0;
		for (int i = 0; i < dim; ++i)
			sum+=posarray[i];
		
		if(sum < signal)
			posarray[rand.Integer(dim)]=1;
		else if (sum > signal)
			posarray[rand.Integer(dim)]=0;
		else
			break;
	}

	//Plot the perturbation on the matrix
	unsigned int pos[2];
	pos[0] = (unsigned int) ((a[0]/xmax) * (float)n);
	pos[1] = (unsigned int) ((a[1]/ymax) * (float)m);

	if(pos[0]==n)
		pos[0]-=1;

	if(pos[1]==m)
		pos[1]-=1;

	int refi0 = pos[0] - N/2;

	if (refi0 < 0)
		refi0 = 0;

	int reff0 = refi0 + N;
	if (reff0 >= n)
		reff0 = n-1;

	int refi1 = pos[1] - M/2;
	if (refi1 < 0)
		refi1 = 0;

	int reff1 = refi1 + M;
	if (reff1 >= m)
		reff1 = m-1;	

	for(int i = refi0; i < reff0; ++i){
		for (int j = refi1; j < reff1; ++j)
			grid[i][j] = posarray[(i-refi0)*M + (j-refi1)];
	}

	cout << __PRETTY_FUNCTION__ << endl;

	return GetSparse(grid);
}

TH2C PixelDet::DrawEvent()
{
	TH2C h2("draw_event","Event Plot", n, 0, xmax, m, 0, ymax);

	float razx = xmax/n;
	float razy = ymax/m;

	for (int i = 0; i < n; ++i){
		for(int j= 0; j < m; ++j){
			if(grid[i][j]==1)
				h2.Fill(i*razx, j*razy, 1);
		}
	}

	return h2;
}

event PixelDet::RecEvent(unsigned int N, unsigned int M, unsigned int signal)
{
	event detect;

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			int sum = 0;
			for(int Ni = 0; Ni < N && i + Ni < n; Ni++){
				for(int Mi = 0;Mi < M && j + Mi < m; Mi++)
					sum+=grid[i+Ni][j+Mi];
			}

			if(sum >= signal)
			{
				//we got a hit!

				detect.success = 1;
				detect.n = sum;

				for(int Ni = 0; Ni < N; Ni++){
					for(int Mi = 0; Mi < M; Mi++){
						if(grid[i+Ni][j+Mi])
							detect.pixels.push_back((i+Ni)*m + j + Mi);
					}
				}

				detect.x = (float)(i + N/2) / ((float)n) * xmax;
				detect.y = (float)(j + M/2) / ((float)m) * ymax;

				cout << "Success!" << endl;
				cout << "Particle detected at coords: x = " << detect.x << " y = " << detect.y << " (mm)" << endl << endl;

				for (int i = 0; i < detect.pixels.size(); ++i)
					cout << " Pixel [" << i << "] = " << detect.pixels[i] << endl;

				cout << __PRETTY_FUNCTION__ << endl;

				return detect;
			}	
		}
	}

	cout << "No signal detected... only noise!" << endl;

	detect.success = 0;

	cout << __PRETTY_FUNCTION__ << endl;

	return detect;
}

vector<int> PixelDet::GetSparse(int** matrix, unsigned int N, unsigned int M)
{
	vector<int> v;
	for (int k=0, i=0; i < N; ++i){
		for(int j=0; j < M; ++k, ++j){
			if(matrix[i][j])
				v.push_back(k);
		}
	}

	cout << __PRETTY_FUNCTION__ << endl;

	return v;
}

int** PixelDet::GetMatrix(std::vector<int> v, unsigned int N, unsigned int M)
{
	int** matrix = new int* [N];
	for(int i = 0; i < N; ++i)
		matrix[i] = new int [M];

	for (int k=0, i=0, l=0; i < N; ++i){
		for(int j=0; j < M; ++k, ++j)
		{	
			if(v[l]==k)
			{
				matrix[i][j]=1;
				l++;
			}
			else
				matrix[i][j]=0;
		}
	}

	cout << __PRETTY_FUNCTION__ << endl;

	return matrix;
}

void PixelDet::DumpEvent()
{
	for (int i = 0; i < n; ++i)
		delete [] grid[i];
	delete [] grid;

	grid = new int* [n];

	for (int i = 0; i < n; ++i)
		grid[i]= new int [m];

	cout << __PRETTY_FUNCTION__ << endl;
}