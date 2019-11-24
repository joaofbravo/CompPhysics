#ifndef __cTrab1__
#define __cTrab1__

#include <string>
using namespace std;

enum poloperations_t {
  P, Q, R, S, T, U
};

enum groups_t {
    A01, A02, A03, A04, A05, A06, A07, A08, A09, A10, A11, A12,
    B01, B02, B03, B04, B05, B06, B07, B08, B09, B10, B11, B12,
    C01, C02, C03, C04, C05, C06, C07, C08
};

class cTrab1 {
public:
  cTrab1();
  ~cTrab1() {
    delete [] ir;
  }
  string SetRandomSequence(); 
  string GetPolOperations(groups_t);
  static double P8(double); //gives me the (x-1)^8 result
 private:
  int *ir; //random sequence
};

#endif
