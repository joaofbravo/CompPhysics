#include <string>
#include <map>

#ifndef __ATOM__
#define __ATOM__

typedef struct{
	unsigned short int Z;
	float A;
	float mass;

} ATOM;

#endif

void print(std::map<std::string, ATOM*>&);