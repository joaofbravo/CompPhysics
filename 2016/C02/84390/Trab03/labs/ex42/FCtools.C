#include "FCtools.h"
#include "FCmatrixFull.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<string> FCtools::ReadFileToString(string filename)
{
	ifstream F(filename);

	if(!F.is_open())
	{
		cout << "File " << filename << " not found." << endl;
		exit (1);
	}

	vector<string> ret;
	string line;

	while (!F.eof()) 
	{
		getline(F, line);
		ret.push_back(line);
	}

    F.close();

    return ret;
}

vector<Vec> FCtools::ReadFileToVecVector(string filename)
{
	ifstream F(filename);

	if(!F.is_open())
	{
        cout << "File " << filename << " not found." << endl;
        exit (1);
    }

    string line;
    double x;
    vector<double> aux;
    vector<Vec> ret;

    while(!F.eof())
    {
    	getline(F,line);

    	stringstream s(line);
    	
    	while (s >> x)
            aux.push_back(x);

        ret.push_back(Vec(aux));
        aux.clear();
    }

    F.close();

    return ret;
}

Vec FCtools::ReadFileToVec(string filename)
{
    ifstream F(filename);

    if(!F.is_open())
    {
        cout << "File " << filename << " not found." << endl;
        exit (1);
    }

    double x;
    vector<double> vectorD;

    while(F >> x)
        vectorD.push_back(x);

    F.close();

    return Vec(vectorD);
}

Vec* FCtools::ReadFileToVecP(string filename, int n)
{
    ifstream F(filename);

    if(!F.is_open())
    {
        cout << "File " << filename << " not found." << endl;
        exit (1);
    }

    string line;
    double x;
    vector<double> aux;
    Vec* ret = new Vec[n];

    for (int i = 0; !F.eof() && i < n; ++i) {
        getline(F,line);

        stringstream s(line);
        
        while (s >> x)
            aux.push_back(x);

        ret[i] = Vec(aux);

        aux.clear();
    }

    if (!F.eof())
        cout << __PRETTY_FUNCTION__ << ": You did not reach the end of the file." << endl;
    else if (F.eof())
        cout << __PRETTY_FUNCTION__ << ": You reached the end of the file." << endl;

    F.close();

    return ret;
}

FCmatrixFull FCtools::ReadFileToMatrix(string filename)
{
    ifstream F(filename);

    if(!F.is_open())
    {
        cout << "File " << filename << " not found." << endl;
        exit (1);
    }

    string line;
    double x;
    vector<double> aux;
    vector<Vec> matV;

    while(!F.eof())
    {
        getline(F,line);

        stringstream s(line);
        
        while (s >> x)
            aux.push_back(x);

        matV.push_back(Vec(aux));
        aux.clear();
    }

    F.close();

    return FCmatrixFull(matV);
}