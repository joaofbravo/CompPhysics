#include "point1Dn.h"
#include <cstdio>

point1Dn::point1Dn(double fx) : px(new double(fx)) {
	printf("[%s] constructor called with x=%f \n", __PRETTY_FUNCTION__, fx);
}

point1Dn::point1Dn(double* fx) : px(new double(*fx)) {
	printf("[%s] constructor called with x=%f \n", __PRETTY_FUNCTION__, *fx);
}

point1Dn::~point1Dn() {
	delete px;
	printf("[%s] destructor called\n", __PRETTY_FUNCTION__);
}


void point1Dn::SetX(double fx) {
	*px = fx; //value placed on variable pointed by px
	printf("[%s] value =%f\n", __PRETTY_FUNCTION__, fx);
}

double point1Dn::X() {return *px;}

void point1Dn::print() {
	printf("[%s] this adress=%p X=%f \n", __PRETTY_FUNCTION__, this, this->X()); // this-> é opcional
}