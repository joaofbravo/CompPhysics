#ifndef __FCmatrix__
#define __FCmatrix__

#include <vector>
#include <string>
#include "Vec.h"

using namespace std;

class FCmatrix {
 public: 

  // constructors
  FCmatrix(double**, int n, int m);
  FCmatrix(double*, int n, int m);
  FCmatrix(vector<Vec>);

  // operators
  virtual Vec& operator[](int); // allows to insert a vector into the matrix
  virtual const Vec& operator[](int) const; // return vector and do not touch on matrix

  // Get methods
  virtual const Vec& GetRow(int) const = 0;   
  virtual Vec GetCol(int) const = 0;   
  virtual const int GetNrows() const = 0;

  // tools
  virtual void Print() const;

 protected:
  vector<Vec> M;
  string classname;

};

#endif