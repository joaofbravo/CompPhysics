#include <vector>
#include <map>
#include <string>

using namespace std;

vector< vector<int>* >* GetMatrix(int, int, int=0);

vector< vector<int>* >* Mmapfind(map <string, vector< vector<int>* >* >&, string);

void Mvecprint(vector< vector<int>* >*);

void Mvecdelete(vector< vector<int>* > *);