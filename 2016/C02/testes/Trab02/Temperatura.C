#include "FCtools.h"
#include "FCmatrixFull.h"
#include "FCtools.h"
#include "EqSolver.h"
#include "cFCgraphics.h"
#include "Spline3Interpolator.h"
#include <iostream>

using namespace std;

int main () {

  FCtools reader;
  
  //matriz de coeficientes
  FCmatrixFull M(reader.ReadFileToMatrix("txt/matriz.data"));

  //vector of constants B
  Vec B(reader.ReadFileToVec("txt/constantes.data"));

  // cout << M.size() << endl;
  // cout << M[0].size() << endl;
  // cout << B.size() << endl;

  //solving M T = B
  EqSolver SOLVER(M, B);
  Vec T = SOLVER.GaussEliminationSolver();
  T.Print();
  
  //determinant
  double D = SOLVER.Determinant();
  cout << endl << D << endl;

  //SOLVER.Print();

  // make plots
  double x[100];
  double Tv[100];

  for (int i = 0; i < 100; ++i)
  {
      x[i] = i;
      Tv[i] = T[i];
  }

  Spline3Interpolator Interpol(100,x,Tv);
  Interpol.Draw();

  return 0;
}