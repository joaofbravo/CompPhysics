#include "ConstantsManager.h"
#include <iostream>
#include <sstream>
#include <limits>


using namespace std;

void GetFromScreen(string message, double& object);

ConstantsManager::ConstantsManager(string element,string data) :  IN(data) , OUT(data,std::ios::app)
{
	string line;
	
	if(!(IN.is_open() && OUT.is_open()))
	{
		cout << __PRETTY_FUNCTION__ <<" ERROR!!! File "<< data <<" not found!!!" << endl;
	}

	for (int i = 0; i < 3; ++i)
	{
		getline(IN,line);
		// cout << line <<endl;
	}

	IN >> me >>Re >>Na >>alpha >>areamassa;
	
	SetElement(element);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ConstantsManager::~ConstantsManager()
{
	IN.close();
	OUT.close();

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ConstantsManager::AddElement(string element)
{
	cout << "Adding Element " << element <<endl;
	cout << "Source: http://www-pdg.lbl.gov/2016/AtomicNuclearProperties/index.html"<<endl;
	GetFromScreen("Please provide atomic number: ",Z);
	GetFromScreen("Please provide atomic mass: ",A);
	GetFromScreen("Please provide volumetric density (g/cm^3): ",P);
	GetFromScreen("Please provide Radiation Lenght: ",X0);
	cout << "Source: http://fcomp.ist.utl.pt/ComputPhys.web/Trabalhos.2016/Projecto/tabela.Penelope.pdf"<<endl;
	GetFromScreen("Please provide RmeC/(ℏ) : ",Rmech);
	cout << "Source: http://fcomp.ist.utl.pt/ComputPhys.web/Trabalhos.2016/Projecto/tabela.Leo.pdf" << endl;
	GetFromScreen("Please provide C0 : ",C0);
	GetFromScreen("Please provide a : ",a);
	GetFromScreen("Please provide U0 : ",U0);
	GetFromScreen("Please provide U1 : ",U1);
	GetFromScreen("Please provide m : ",m);


	OUT << endl << element<< " " << Z << " " << A << " "	<< P << " "<< X0<<" " << Rmech << " " << C0 << " " << a << " " << U0 << " " << U1 << " " <<m;
	OUT.flush();


	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

void GetFromScreen(string message, double& object)
{
	cout << message;
	if(!(cin >> object))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Error reading argument" <<endl;
		GetFromScreen(message,object);
	}
}

void ConstantsManager::SetElement(string element)
{
	IN.clear();
    IN.seekg(0, ios::beg);
    
	bool found = false;
	string line;

	while (getline(IN, line)) 
	{
		// cout << line <<endl;
        if (line.find(element) != string::npos) 
        {
        	found = true;
        	break;
        }
    }

	string name;

    if(found)
	{
    	stringstream s(line);
    	s >> name >> Z >> A >> P >> X0 >>Rmech >> C0 >> a >> U0 >>U1 >> m;
    }
    else
    {
    	int answer;
    	cout << "Element "<< element << " not found!!! Do you want to insert it to the database, or use Aluminium instead?"<< endl;
    	cout << "Insert 1 for database, anything else for Aluminium: ";
    	cin >> answer;
    	if(answer == 1)
    	{
    		AddElement(element);
    		
			IN.clear();
    		IN.seekg(0, ios::beg);

			while (getline(IN, line)) 
			{
			    if (line.find(element) != string::npos) 
			    	break;
			}
			stringstream s(line);
    		s >> name >> Z >> A >> P >>X0 >>Rmech >> C0 >> a >> U0 >>U1 >> m;
    	}
    	else
    	{
    		element = "Aluminium";
    		
    		IN.clear();
    		IN.seekg(0, ios::beg);
						
			while (getline(IN, line)) 
			{
			    if (line.find(element) != string::npos) 
			    	break;
			}

			stringstream s(line);
    		s >> name >> Z >> A >> P >> X0 >>Rmech >> C0 >> a >> U0 >>U1 >> m;
    	}	
    }

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ConstantsManager::Print()
{
	cout << "me: " << me <<endl;
	cout << "Re: " << Re <<endl;
	cout << "Na: " << Na <<endl;
	cout << "alpha: " << alpha <<endl;
	cout << "areamassa: " << areamassa <<endl;
	cout << "Z: " << Z <<endl;
	cout << "A: " << A <<endl;
	cout << "P: " << P <<endl;
	cout << "X0: "<< X0 <<endl;
	cout << "Rmech: " << Rmech <<endl;
	cout << "C0: " << C0 <<endl;
	cout << "a: " << a <<endl;
	cout << "U0: " << U0 <<endl;
	cout << "U1: " << U1 <<endl;
	cout << "m: " << m <<endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}