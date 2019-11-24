#ifndef __cSUN__
#define __cSUN__ 

#include <string>
#include <vector>
#include "TROOT.h"
#include "TGraph.h"

	typedef struct
	{
	  float time;
	  float b;
	} sB;

	typedef struct
	{
	  float time;
	  float n;
	} sSPOTS;

	typedef struct
	{
	  float time;
	  float n;
	} sNM;
	
class cSUN{

public:
	cSUN(){;}
	~cSUN(){;}

	void ReadFile(std::string, std::string);

	void GetB(std::vector<sB>&);
	void GetSunSpots(std::vector<sSPOTS>&);
	void GetMonitorCounts(std::vector<sNM> &);

	TGraph* GetB(std::string, std::string);
  	TGraph* GetSPOTS(std::string, std::string);
  	TGraph* GetNM(std::string, std::string);

private:
	std::vector <sB> vB;
	std::vector <sSPOTS> vSPOTS;
	std::vector <sNM> vNM;
};

#endif