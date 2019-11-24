#include "pointSorter.h"
#include <iostream>

using namespace std;

int main() {
  // make a vector with points
  vector<point*> vP;
  vP.push_back(new point(1,1));
  vP.push_back(new point(4,1));
  vP.push_back(new point(1,4));
  vP.push_back(new point(2,1));
  vP.push_back(new point(5,1));

  // sort points by norma
  pointSorter S(vP);

  cout << "Original Vec:" << endl;  
  for (int i=0; i < S.size(); i++) {
    S[i]->Print(); //print coordinates and norma
  }
  cout << endl;

  vector<point*> VPsorted0 = S.sort(+1); // [0] < [1] < [2] < ...(ascending order)
  vector<point*> VPsorted1 = S.sort(-1); // [0] > [1] > [2] > ... (descending order)
  vector<point*> VPsorted2 = S.sort(0); // returns  original vector

  // print vector sorted (make a loop using vector iterator)
  vector<point*>::iterator Vit;

  cout << "Ascending:" << endl;
  for (Vit = VPsorted0.begin(); Vit != VPsorted0.end(); ++Vit){
    (*Vit)->Print();
    cout << endl;
  }

  cout << endl;

  cout << "Descending:" << endl;  
  for (Vit = VPsorted1.begin(); Vit != VPsorted1.end(); ++Vit){
    (*Vit)->Print(); 
    cout << endl;
  }
  cout << endl;

  cout << "Original Vec:" << endl;  
  for (Vit = VPsorted2.begin(); Vit != VPsorted2.end(); ++Vit){
    (*Vit)->Print(); 
    cout << endl;
  }
  cout << endl;

  // delete heap objects
  for(int i =0; i < VPsorted0.size();++i)
  {
    delete VPsorted0[i];
    delete VPsorted1[i];
    delete VPsorted2[i];
  }

  return 0;
}