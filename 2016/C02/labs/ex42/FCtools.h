#ifndef __FCtools__
#define __FCtools__

#include "Vec.h"
#include "FCmatrixFull.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class FCtools {
public:
	FCtools(){;}
	~FCtools(){;}

	vector<string> ReadFileToString(string); //file name, returns lines
	vector<Vec> ReadFileToVecVector(string); //file name, returns vectors of Vec’s
	Vec ReadFileToVec(string); //file name, returns Vec
	Vec* ReadFileToVecP(string, int); //file name, returns pointer to array of Vec’s, int provides number of lines
	FCmatrixFull ReadFileToMatrix(string); //file name, returns Matrix
};

#endif