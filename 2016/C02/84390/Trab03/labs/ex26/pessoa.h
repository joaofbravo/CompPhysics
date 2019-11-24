#include <string>

#ifndef __pessoa__
#define __pessoa__

using namespace std;

class pessoa {
public:
	//constructor (nome, data de nascimento)
	pessoa(string="Nobody", unsigned int=0);
	~pessoa();

	void SetName(string);
	void SetBornDate(unsigned int);
	string GetName();
	unsigned int GetBornDate();
	virtual void Print();

private:
	string name; //nome
	unsigned int DataN; //data de nascimento
};

pessoa** DoArray(int=1, string="Nobody", unsigned int=0);

#endif