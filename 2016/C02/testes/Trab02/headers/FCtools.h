#ifndef __FCtools__
#define __FCtools__

#include <string>
#include <vector>
#include "Vec.h"

using std::string;
using std::vector;
class FCmatrixFull;

class FCtools {
public:
	FCtools(){;}
	~FCtools(){;}

	vector<string> ReadFileToString(string); //file name, returns lines
	FCmatrixFull ReadFileToMatrix(string); //file name, returns vectors of Vec’s
	Vec ReadFileToVec(string); //file name, returns vectors of Vec’s
	Vec* ReadFileToVec(string, int); //file name, returns pointer to array of Vec’s, int provides number of lines
};

#endif