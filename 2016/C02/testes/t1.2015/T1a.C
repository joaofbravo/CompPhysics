#include "point.h"

int main () {

  // make points
  point P1(1.,1.);
  point P2(2.,5.);

  // additional points
  point P3(P1+P2); // (x1+x2, y1+y2)
  point P4(P1*P2); // (x1*x2, y1*y2)
  point P5(P1-P2); // (x1-x2, y1-y2)

  // returns "norma"
  float norma_1 = !P1; // sqrt(x1*x1+y1*y1)

  // print point
  P1.Print();

  return 0;
}
