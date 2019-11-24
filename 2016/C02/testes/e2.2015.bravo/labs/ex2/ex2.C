#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

double f(double x);

int main(int argc, char*argv[])
{
    if(argc!=2)
    {
        cout << "Introduza um valor como argumento" << endl;
        return -1;
    }

    double x = atof(argv[1]), z;

    z = x + f(x);

    cout << "z(x)= " << z << endl;

    return 0;
}


double f(double x)
{
    return sin(x)*sin(x);
}