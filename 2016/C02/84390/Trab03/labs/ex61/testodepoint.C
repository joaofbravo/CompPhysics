#include "ODEpoint.h"
#include <iostream>

using namespace std;

int main() {

    //default constructor / operators test
    double a[] = {0.,1,2,3.5};
    ODEpoint point(4,a);
    Vec vec(4,a);
    point += vec;
    point += point;
    point.Print();
    cout << "-------------" << endl;

    //copy constructors test
    Vec aa(4,a);
    ODEpoint bb(aa); 
    ODEpoint zz(bb);
    bb.Print();
    zz.Print();
    cout << "-------------" << endl;

    //move constructors test
    ODEpoint dd = aa + bb;
    ODEpoint ee = aa; //copy
    ODEpoint ff = bb; //copy
    dd.Print();
    ee.Print();
    ff.Print();
    cout << "-------------" << endl;

    ODEpoint cc2 = move(ODEpoint(1, a));
    ODEpoint dd2 = move(aa + bb);
    ODEpoint ee2 = move(aa);
    ODEpoint ff2 = move(bb);
    cc2.Print();
    dd2.Print();
    ee2.Print();
    ff2.Print();
    cout << "-------------" << endl;

    //assignments test
    ODEpoint b;
    ODEpoint pp(3,a);
    b = pp;
    b = vec;
    b = pp + pp;
    b = pp + vec;
    b = move(pp + pp);
    b = move(vec);
    b = move(pp);
    b.Print();
    cout << "-------------" << endl;

    int dim = b.Dim();
    cout << dim << endl;
    cout << b.T() << endl;
    cout << b.X(0) << endl;
    cout << b.X(1) << endl;
    cout << "-------------" << endl;

    double* c = b.GetArray();
    for (int i = 0; i < dim+1; ++i)
        cout << c[i] << endl;

    return 0;
}