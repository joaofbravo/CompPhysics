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

    double x;
    vector<double> cicle;
    vector<Vec> matV;

    string line;

    while(!F.eof())
    {
    	getline(F,line);

    	stringstream s(line);
    	
    	while (s >> x)
            cicle.push_back(x);

        matV.push_back(Vec(cicle));
        cicle.clear();
    }

    FCmatrixFull ret(matV);
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

    Vec ret(vectorD);
    return ret;
}

Vec* FCtools::ReadFileToVec(string filename, int n)
{
    ifstream F(filename);

    if(!F.is_open())
    {
        cout << "File " << filename << " not found." << endl;
        exit (1);
    }

    double x;
    vector<double> cicle;
    vector<Vec> ret;

    string line;

    while(ret.size() < n)
    {
        getline(F,line);

        stringstream s(line);
        
        while (s >> x)
            cicle.push_back(x);

        ret.push_back(Vec(cicle));
        cicle.clear();
    }

    Vec* result = new Vec[ret.size()];

    for (int i = 0; i < ret.size(); ++i)
        result[i] = ret[i];

    return result;
}