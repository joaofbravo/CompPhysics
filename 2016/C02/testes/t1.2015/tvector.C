#include "point.h"
#include <vector>
#include <iostream>

using namespace std;

// prototypes
vector <point> GetVector();

// main program
int main() {
  vector <point> V = GetVector();

  return 0;
}

// functions

vector <point> GetVector() {
  int n = 5;
  vector <point> vP(n);

  for (int i = 0; i < n; i++)
  {
    vP[i] = point(1.,2.);
  }

  return vP;
}
