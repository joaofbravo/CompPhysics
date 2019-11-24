#include "ODEsolver.h"
#include "ODEdrawer.h"
#include "TMath.h"
#include <iostream>

using namespace std;

int main() {

    //ex 66: Non linear pendulum without friction

    //m = 1Kg, l = 1m
    //t = x[0]; theta = x[1]; omega = x[2]
    //d^2theta/dt^2 = -g/l*sin(theta) - b/m*omega

    //var. dependentes: theta e omega

    vector<TFormula> v;
    v.push_back(TFormula("0","x[2]"));
    v.push_back(TFormula("1","-9.8*sin(x[1])-0*x[2]"));
    ODEsolver Pendulo(v);
    v.clear();

    Vec i(3,0.);
    i[0] = 0;
    i[1] = 70*M_PI/180.;
    i[2] = 0;

    double step = 0.01;

    // iterativos:
    vector<ODEpoint> vE = Pendulo.Euler(ODEpoint(i), step, 20);
    vector<ODEpoint> vP = Pendulo.PredictorCorrector(ODEpoint(i), step, 20);
    vector<ODEpoint> vRK2 = Pendulo.RK2(ODEpoint(i), step, 20);
    vector<ODEpoint> vRK4 = Pendulo.RK4(ODEpoint(i), step, 20);

    // Energia!
    vector<ODEpoint> vRK4energy = vRK4;
    for (int i = 0; i < vRK4energy.size(); ++i){
        vRK4energy[i][1] = 0.5*vRK4[i][2]*vRK4[i][2] + (1-cos(vRK4[i][1]))*9.8;
    }

    // Amplitude!
    vector<ODEpoint> vRK4amp = vRK4energy;
    for (int i = 0; i < vRK4amp.size(); ++i){
        vRK4amp[i][1] = acos(1-vRK4energy[i][1]/9.8);
    }

    vector< vector<ODEpoint> > vectorvec;
    vectorvec.push_back(vE);

    ODEdrawer a1;
    vector<Color_t> clr1(1, kBlue);

    a1.AddPad(vectorvec, 0, 1, 2, "Euler;t (s);#theta (rad);#omega (rad/s)", "P0", clr1);

    vectorvec[0]=vP;
    a1.AddPad(vectorvec, 0, 1, 2, "PredictorCorrector;t (s);#theta (rad);#omega (rad/s)", "P0", clr1);

    vectorvec[0]=vRK2;
    a1.AddPad(vectorvec, 0, 1, 2, "RK2;t (s);#theta (rad);#omega (rad/s)", "P0", clr1);

    vectorvec[0]=vRK4;
    a1.AddPad(vectorvec, 0, 1, 2, "RK2;t (s);#theta (rad);#omega (rad/s)", "P0", clr1);

    vectorvec[0]=vRK4;
    a1.AddPad(vectorvec, 1, 2, "RK2; #theta (rad);#omega (rad/s)", "AC", clr1);

    vectorvec[0]=vRK4energy;
    a1.AddPad(vectorvec, 0, 1, "Pendulum Energy;t (s);E (j)", "AP", clr1);

    vectorvec[0]=vRK4amp;
    a1.AddPad(vectorvec, 0, 1, "Pendulum amplitude;t (s);#theta (rad)", "AP", clr1);

    a1.Draw();
    a1.Print("execs/nonlinearpendulum.pdf");

    //==============================

    //ex 67: Temperature of a bar

    // a(x)y′′(x) + b(x)y′(x) + c(x)y(x) = f(x)
    //WARNING: dont use more than 1000 points or it will caput

    v.push_back(TFormula("a","1"));
    v.push_back(TFormula("b","0"));
    v.push_back(TFormula("c","0"));
    v.push_back(TFormula("f","0"));

    ODEsolver FD(v);
    v.clear();

    //t0, tf, y0 ou y'0, yf ou y'f, step, true se escolher derivadas
    vector<ODEpoint> vec = FD.FiniteDiff(0,1, 40,10, 0.01, false,false);
    vector< vector<ODEpoint> > vecvector (1, vec);

    v.push_back(TFormula("a","1"));
    v.push_back(TFormula("b","0"));
    v.push_back(TFormula("c","-4*17./(206.*1.01)"));
    v.push_back(TFormula("f","-4*17./(206.*1.01*23)"));

    FD.SetODEfunc(v);

    vecvector.push_back(FD.FiniteDiff(0,1, 40,0, 0.01, false,true));

    ODEdrawer a2;
    a2.AddPad(vecvector, 0, 1, "Temperature of the Bar;x (m);T (k)", "AP", clr1);
    a2.Draw();
    a2.Print("execs/Temperatura.pdf");

    return 0;
}