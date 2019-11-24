//
// Fisica Computacional (MEFT)
// F Barao (Nov 2016)
//
// FCmatricFull class
//
// Notes:
// It's good to declare all Get methods as const (otherwise we have problems every time a const matrix call them)
//


#ifndef __FCmatrixFull__
#define __FCmatrixFull__

#include "FCmatrixFull.h"
#include "FCmatrix.h"
#include "Vec.h"
#include <cstdio>

class FCmatrixFull : public FCmatrix {
 public:

  // constructors
  FCmatrixFull(vector<Vec>);
  FCmatrixFull(double* va=NULL, int fnL=0, int fnC=0);
  FCmatrixFull(double** va=NULL, int fnL=0, int fnC=0);

  // Get methods
  const Vec& GetRow(int i) const; 
  Vec GetCol(int i) const;
  const int GetNrows() const;

 // operator sum
  FCmatrixFull operator+(const FCmatrix&); 

 // tools
  void Print() const;
};

#endif