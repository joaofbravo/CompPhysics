#include "Box.h"
#include <cstdlib>

using namespace std;

const Box& Box::operator=(const Box& b){
	if(this != &b){
		x = b.x;
		y = b.y;
		z = b.z;
	}

	cout << __PRETTY_FUNCTION__ << endl;
	return *this;
}

Box Box::operator+(const Box& b){
	cout << __PRETTY_FUNCTION__ << endl;

	//nao se deve comparar doubles assim
	if( x == b.x && y == b.y){
		return Box(x, y, z+b.z);
	} else if( x == b.x && z == b.z){
		return Box(x, y+b.y, z);
	} else if( y == b.y && z == b.z){
		return Box(x+b.x, y, z);
	} else {
		cout << "Boxes cannot be added because more than one side is different." << endl;
		exit(1);
	}
}

// Método algo redundante...
Box* Box::Add_pB(const Box* pB){
	cout << __PRETTY_FUNCTION__ << endl;

	//nao se deve comparar doubles assim
	if( x == pB->x && y == pB->y){
		return new Box(x, y, z+pB->z);
	} else if( x == pB->x && z == pB->z){
		return new Box(x, y+pB->y, z);
	} else if( y == pB->y && z == pB->z){
		return new Box(x+pB->x, y, z);
	} else {
		cout << "Boxes cannot be added because more than one side is different." << endl;
		exit(1);
	}
}

float Box::GetVolume(){
	cout << __PRETTY_FUNCTION__ << endl;
	return x*y*z;
}