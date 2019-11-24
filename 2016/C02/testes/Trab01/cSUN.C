#include "cSUN.h"
#include <fstream>
#include <iostream>

using namespace std;

void cSUN::ReadFile(string file, string type){
	ifstream F;
	F.open(file);

	string line;
	int year, month, day;
	float val;

	if(!F.is_open())
	{
		cout << "File not found !!!" << endl;
		return;
	}
	else if (type != "B" && type != "SPOTS" && type != "NM") {
		cout << "The input type does not exist." << endl;
		return;
	}

	while (!F.eof()) {
		getline(F, line);
		cout << line << endl;

		year = atoi(line.substr(0,4).c_str());  //cout << year << endl;
		month = atoi(line.substr(5,7).c_str()); //cout << month << endl;
		day = atoi(line.substr(8,10).c_str());  //cout << day << endl;
		val = atof(line.substr(11).c_str());    //cout << val << endl;
		float time = (year-1700)*365.25 + (month-1)*30.4375 + day;

		// ifs deveriam estar fora, assim só se faziam uma vez
		if(type == "B"){
			sB st = {time, val};
			vB.push_back(st);
		}
		else if (type == "SPOTS"){
			sSPOTS st = {time, val};
			vSPOTS.push_back(st);
		}
		else if (type == "NM"){
			sNM st = {time, val};
			vNM.push_back(st);		
		}
	}

	F.close();
}

void cSUN::GetB(vector<sB>& vec){
	for (unsigned int i = 0; i < vB.size(); ++i){
		vec.push_back(vB[i]);
	}
}

void cSUN::GetSunSpots(vector<sSPOTS>& vec ){
	for (unsigned int i = 0; i < vSPOTS.size(); ++i)
		vec.push_back(vSPOTS[i]);
}

void cSUN::GetMonitorCounts(vector<sNM> &vec){
	for (unsigned int i = 0; i < vNM.size(); ++i)
		vec.push_back(vNM[i]);
}


TGraph* cSUN::GetB(string sTi, string sTf)
{
	int yeari = atoi(sTi.substr(0,4).c_str());  //cout << yeari << endl;
	int monthi = atoi(sTi.substr(5,7).c_str()); //cout << monthi << endl;
	int dayi = atoi(sTi.substr(8,10).c_str());  //cout << dayi << endl;

	int yearf = atoi(sTf.substr(0,4).c_str());  //cout << yearf << endl;
	int monthf = atoi(sTf.substr(5,7).c_str()); //cout << monthf << endl;
	int dayf = atoi(sTf.substr(8,10).c_str());  //cout << dayf << endl;

	float Ti = (yeari-1700)*365.25 + (monthi-1)*30.4375 + dayi;
	float Tf = (yearf-1700)*365.25 + (monthf-1)*30.4375 + dayf;
	
	int i = 0;

	if(Tf<Ti)
	{
		float c = Ti;
		Ti = Tf;
		Tf= c;
	}

	cout << Ti << endl;
	cout << Tf << endl;
	cout << vB[vNM.size()-1].time << endl;

	vector<sB>::iterator it = vB.begin();

	while(vB[i].time<Ti)
	{
		++i;
		++it;
	}
	
	float t[vB.size()-i-1];
	float val[vB.size()-i-1];
	int j =0;

	for (j=0, it; it!=vB.end(); ++it, j++)
	{
		t[j]=it->time;
		val[j]=it->b;	
	}

	TGraph* g1 = new TGraph(vB.size()-i-1,t,val);

	return g1;
}

TGraph* cSUN::GetSPOTS(string sTi, string sTf)
{
	int yeari = atoi(sTi.substr(0,4).c_str());  //cout << yeari << endl;
	int monthi = atoi(sTi.substr(5,7).c_str()); //cout << monthi << endl;
	int dayi = atoi(sTi.substr(8,10).c_str());  //cout << dayi << endl;

	int yearf = atoi(sTf.substr(0,4).c_str());  //cout << yearf << endl;
	int monthf = atoi(sTf.substr(5,7).c_str()); //cout << monthf << endl;
	int dayf = atoi(sTf.substr(8,10).c_str());  //cout << dayf << endl;

	float Ti = (yeari-1700)*365.25 + (monthi-1)*30.4375 + dayi;
	float Tf = (yearf-1700)*365.25 + (monthf-1)*30.4375 + dayf;
	
	int i = 0;

	if(Tf<Ti)
	{
		float c = Ti;
		Ti = Tf;
		Tf= c;
	}

	cout << Ti << endl;
	cout << Tf << endl;
	cout << vSPOTS[vSPOTS.size()-1].time << endl;

	vector<sSPOTS>::iterator it = vSPOTS.begin();

	while(vSPOTS[i].time<Ti)
		{
			++i;
			++it;
		}
	
	float t[vSPOTS.size()-i-1];
	float val[vSPOTS.size()-i-1];
	int j =0;

	for (j=0, it; it!=vSPOTS.end(); ++it, j++)
	{
		t[j]=it->time;
		val[j]=it->n;	
	}

	TGraph* g1 = new TGraph(vSPOTS.size()-i-1,t,val);

	return g1;
}

TGraph* cSUN::GetNM(string sTi, string sTf)
{
	int yeari = atoi(sTi.substr(0,4).c_str());  //cout << yeari << endl;
	int monthi = atoi(sTi.substr(5,7).c_str()); //cout << monthi << endl;
	int dayi = atoi(sTi.substr(8,10).c_str());  //cout << dayi << endl;

	int yearf = atoi(sTf.substr(0,4).c_str());  //cout << yearf << endl;
	int monthf = atoi(sTf.substr(5,7).c_str()); //cout << monthf << endl;
	int dayf = atoi(sTf.substr(8,10).c_str());  //cout << dayf << endl;

	float Ti = (yeari-1700)*365.25 + (monthi-1)*30.4375 + dayi;
	float Tf = (yearf-1700)*365.25 + (monthf-1)*30.4375 + dayf;
	
	int i = 0;

	if(Tf<Ti)
	{
		float c = Ti;
		Ti = Tf;
		Tf= c;
	}

	cout << Ti << endl;
	cout << Tf << endl;
	cout << vNM[vNM.size()-1].time << endl;

	vector<sNM>::iterator it = vNM.begin();

	while(vNM[i].time<Ti)
		{
			++i;
			++it;
		}
	
	float t[vNM.size()-i-1];
	float val[vNM.size()-i-1];
	int j =0;

	for (j=0, it; it!=vNM.end(); ++it, j++)
	{
		t[j]=it->time;
		val[j]=it->n;	
	}

	TGraph* g1 = new TGraph(vNM.size()-i-1,t,val);

	return g1;
}