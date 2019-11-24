#include <string>
#include <vector>

#ifndef __ATOM__
#define __ATOM__

typedef struct{
	std::string name;
	unsigned short int Z;
	float A;
	float mass;

} ATOM;

#endif

void print(std::vector<ATOM*>&);