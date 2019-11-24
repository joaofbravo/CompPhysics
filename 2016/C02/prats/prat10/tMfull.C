//
// Fisica Computacional (MEFT)
// F Barao (Nov 2016)
// example of using FCmatrix and FCmatrixFull classes inheritance
//
// main program
//

#include "FCmatrix.h"
#include "FCmatrixFull.h"
int main() {

  // we start by defining a matrix of elements (3 lines and 5 columns)

  double a[3][5] = {
    {1, 2, 3, 4, 5},
    {11, 12, 13, 14, 15},
    {21, 22, 23, 24, 25},
  };

  // We can now instantiate a FCmatrixFull object M1 by using the constructor
  // accepting a pointer to an array
  // Note: In fact a is a array with all the elements sequentially aligned line by line 

  FCmatrixFull M1( (double*)a, 3, 5 );
  M1.Print();

  // We can now instantiate a FCmatrixFull object M2 by using the constructor
  // accepting a pointer to pointer 

  double **b = new double*[3]; //we need to make 3 line arrays and fill them
  for (int i=0; i<3; i++) {
    b[i] = new double[5];
    b[i] = a[i];
  }
  FCmatrixFull M2( b, 3, 5);
  M1.Print();

  // We are going to add the two matrices M1 and M2 with thn eresult going to M3
  // I'm going to use explicitely the operator+ but that it's completely equivalent
  // to the use of + 

  FCmatrixFull M3 = M1.operator+(M2); 

  // The method Print() was declared as virtual on FCmatrix class and has been redefined 
  // in class FCmatrixFull
  // Every time the objects FCmatrixFull M1 and M2 call Print(), it's the Print(9 function defined
  // on FCmatrixFull class
  // But, if we want explicitely to call the Print() method declared on FCmatrix we can do it: 

  M3.FCmatrix::Print();

  // and now the other Print()

  M3.Print();

}