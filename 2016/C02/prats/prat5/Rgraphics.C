#include <cmath> //exp
#include <cstdlib> // for atof(3)
#include <iostream>
#include <TF1.h> //ROOT TF1
#include "cFCgraphics.h" //my class
using namespace std;

int main(int argc, const char* argv[]) {
	cFCgraphics gr;
	TF1 *f1 = new TF1("FCsinx","sin(x)", 0., 10.);
	
	gr.AddObject(f1);
	gr.AddObject(new TF1("FCexp","exp(x)", 0., 10.));
	gr.AddObject(new TF1("FCsinxx","sin(x)/x", 0., 10.));
	gr.AddObject(new TF1("FClogx","log(x)", 0., 10.));
	
	gr.ListObjects(); // list user stored objects
	
	gr.Draw(); // draw user objects
	gr.Print("Rgraphics.eps"); // save objects
	
	return 0;
}