#include "pointSorter.h"
#include <iostream>


using namespace std;


pointSorter::pointSorter(const vector<point*>& vec){
	pair< map<double, point* >::iterator, bool > success;
	
	double epsilon = 10e-15;
	
	double norma;
	
	for (int i = 0; i < vec.size(); ++i){
		V.push_back(new point (*vec[i]));
		
		norma = !(*V[i]);
		
		while(!(success.second))
		{	
			success = M.emplace(norma, V[i]);
			norma += epsilon;
		}
		
		success.second = false;
	}
}

pointSorter::~pointSorter(){
	for (int i = 0; i < V.size(); ++i)
		delete V[i];
}

point* pointSorter::operator[](int i) {
	if(i > V.size() || i < 0){
		cout << "There is no point in entry " << i << " of this vector." << endl;
		return nullptr;
	}

	return V[i];
}

vector<point*> pointSorter::sort(int op)
{
	vector<point*> ret(M.size());
	map<double,point*>::iterator Mit;
	vector<point*>::iterator Vit;
	int i;

	switch(op){
		case 1:
		for (Mit = M.begin(), i=0; Mit!=M.end(); ++Mit, ++i)
			ret[i] = new point(*(Mit->second));
		return ret;
		
		break;
		case -1:
		for (Mit = --M.end(), i=0; Mit != --M.begin(); --Mit, ++i)		
			ret[i] = new point(*(Mit->second));

		return ret;
		
		break;
		default:
		if(op != 0)
			cout << "Wrong argument for sorting. Original vector will be returned." << endl;

		for (Vit = V.begin(), i=0; Vit != V.end(); ++Vit, ++i)
			ret[i] = new point(*V[i]);
		
		return ret;
	}
}

int pointSorter::size()
{
	return V.size();
}