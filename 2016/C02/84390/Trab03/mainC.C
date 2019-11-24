#include "TFormula.h"
#include "MyFormula.h"

//header in headers/
//src code in src/

using namespace std;

int main() {

	MyFormula F("100.*sin(x)/x"); //string formula no constructor
	
	F.DrawAndSave(0.1, 10.);

	return 0;
}