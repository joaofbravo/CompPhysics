#include "Vec.h"
#include "FCmatrix.h"
#include <cstdio>

FCmatrix::FCmatrix(double** va, int nL, int nC) : classname(""){
  Vec V;
  for (int i=0; i<nL; i++) { //number of lines
    V.SetEntries(nC, va[i]);
    M.push_back(V);
  }
} 

FCmatrix::FCmatrix(double* va, int nL, int nC) : classname("") {
  Vec V;
  for (int i=0; i<nL; i++) { //number of lines
    int k = i*nC;
    V.SetEntries(nC, &va[k]);
    M.push_back(V);
  }
} 

FCmatrix::FCmatrix(vector<Vec> VV) : classname("") {
  M = VV;
} 

Vec& FCmatrix::operator[](int i) {
  printf("address of Vec: %p\n", &M[i]);
  printf("line %d\n", i);
  if (M.size() > i) {
    return M[i];
  } else {
    M.resize(i+1);
    return M[i];
  }
}  

const Vec& FCmatrix::operator[](int i) const {
  printf("Vec line %d\n", i);
  return M[i];
}  

void FCmatrix::Print() const {
  printf("%s \n", __PRETTY_FUNCTION__);
  for (int i=0; i<M.size(); i++) {
    for (int j=0; j<M[i].size(); j++) {
      printf("%4.2f ", M[i][j]);
    }
    printf("\n");
  }

}