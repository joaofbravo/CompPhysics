#include <iostream>

#ifndef __BOX__
#define __BOX__

using namespace std;

class Box {
public:
	// default constructor
	Box(float fx=1, float fy=1, float fz=1) : x(fx), y(fy), z(fz) { cout << __PRETTY_FUNCTION__ << endl;}
	// copy constructor
	Box(const Box& b) : x(b.x), y(b.y), z(b.z) { cout << __PRETTY_FUNCTION__ << endl;}
	// default destructor
	~Box(){ cout << __PRETTY_FUNCTION__ << endl;}

	const Box& operator=(const Box&);
	Box operator+(const Box&);
	Box* Add_pB(const Box*);
	float GetVolume();

private:
	float x;
	float y;
	float z;
};

#endif