#include <cstdio>
#include <vector>
#include "FCmatrixFull.h"
#include "Vec.h"

FCmatrixFull::FCmatrixFull(double* va, int fnL, int fnC) : FCmatrix(va, fnL, fnC) {
  classname = "FCmatrixFull";
  printf("%s called! [ %s %p %d %d ] \n", __PRETTY_FUNCTION__, classname.c_str(), va, fnL, fnC);
}
FCmatrixFull::FCmatrixFull(double** va, int fnL, int fnC) : FCmatrix(va, fnL, fnC) {
  classname = "FCmatrixFull";
  printf("%s called! [ %s %p %d %d ] \n", __PRETTY_FUNCTION__, classname.c_str(), va, fnL, fnC);
}

FCmatrixFull::FCmatrixFull(vector<Vec> V) : FCmatrix(V) { 
  classname = "FCmatrixFull";
}

const Vec& FCmatrixFull::GetRow(int i) const {
  return M[i];
}

Vec FCmatrixFull::GetCol(int j) const {
  // Importante note here:
  // M[i] gives me a Vec element
  // M[i][j] gives me an element of Vec and it works because I defined in my Vec clas the operator[](int) const 
  // ... LOOK at the const at the end of the GetCol method

  int nlin = M.size();
  Vec vcol(nlin);
  for (int i=0; i<nlin; i++) {
    vcol[i] = M[i][j];
  }
  return vcol;
}

const int FCmatrixFull::GetNrows() const {
  printf("%s called! \n", __PRETTY_FUNCTION__);
  return (int)M.size();
}


FCmatrixFull FCmatrixFull::operator+(const FCmatrix& MA) {
  printf("%s\n", __PRETTY_FUNCTION__);
  printf("vector size = %d \n", (int)M.size());
  printf("MA size %d\n", MA.GetNrows());
  Vec S;
  vector<Vec> V;
  for (int i=0; i<M.size(); i++) {
    S = M[i] + MA.GetRow(i);
    V.push_back(S);
  }  
  return FCmatrixFull(V);
}

void FCmatrixFull::Print() const {
  printf("%s\n", __PRETTY_FUNCTION__);
  for (int i=0; i<(int)M.size(); i++) {
    printf("| "); 
    M[i].Print();
  }  

}