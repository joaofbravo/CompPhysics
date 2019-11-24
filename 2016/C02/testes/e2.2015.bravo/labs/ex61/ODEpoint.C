#include "ODEpoint.h"
#include <iostream>

using namespace std;

ODEpoint::ODEpoint(int fndim, const double* x) : Vec(fndim,x)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ODEpoint::ODEpoint(const ODEpoint& point) : Vec((Vec&)point)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ODEpoint::ODEpoint(const Vec& point) : Vec(point)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ODEpoint::ODEpoint(ODEpoint&& point) : Vec((Vec&&)point)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ODEpoint::ODEpoint(Vec&& point) : Vec((Vec&&)point)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ODEpoint::~ODEpoint()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== assignments ===============

const ODEpoint& ODEpoint::operator= (const ODEpoint& point)
{
	Vec::operator=((Vec&)point);
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

const ODEpoint& ODEpoint::operator= (const Vec& point)
{
	Vec::operator=(point);
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

ODEpoint& ODEpoint::operator= (ODEpoint&& point)
{
	Vec::operator=((Vec&&)point);
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

ODEpoint& ODEpoint::operator= (Vec&& point)
{
	Vec::operator=((Vec&&)point);
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

//=============== get methods ===============

int ODEpoint::Dim() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return N-1;
}

double ODEpoint::T() const 
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return entries[0];
}

double ODEpoint::X(int i) const 
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return entries[i+1];
}

double* ODEpoint::GetArray() 
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return entries;
}