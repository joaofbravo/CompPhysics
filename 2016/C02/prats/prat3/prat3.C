#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

int main() {

  // null ptr and const declaration

  int *p1  = nullptr;
  int * p2 = NULL; 

  int a = 10;
  int* const p = &a;
  p1 = &a;
  p2 = &a;
  
  int b = 5;

  printf("p=%p p1=%p p2=%p\n",p, p1, p2);

  const float me=0.511;


  //----------------------------------------

  // STL vector
  /* Vectors are sequence containers representing arrays that can change in size.
     Just like arrays, vectors use contiguous storage locations for their elements, which means that their elements can also
     be accessed using offsets on regular pointers to its elements, and just as efficiently as in arrays. But unlike
     arrays, their size can change dynamically, with their storage being handled automatically by the container.
  */
  vector<int> v(10);
  v[0] = 10;
  v[1] = 12;

  printf("vector size = %d\n", (int)v.size());

  vector<vector<int> > vM1(5);
  vector<int> vc(4);
  vM1[0] = vector<int>(4);
  vM1[1] = vector<int>(4);
  vM1[2] = vc;


  // multi vector
  vector<vector<int> > vM(5, vector<int>(4));

  printf("matrix size=%d\n", (int)vM.size());

  for (int i=0; i<(int)vM.size(); i++) {
    printf("row size=%d\n", (int)vM[i].size());
    for (int j=0; j<(int)vM[i].size(); j++) {
      vM[i][j] = i*vM[i].size() + j;
    }
  }

  // print out
  // accessing directly
  for (int i=0; i<(int)vM.size(); i++) {
    for (int j=0; j<(int)vM[i].size(); j++) {
      printf("vM[%d][%d] = %d\n", i, j, vM[i][j]);
    }
  }
  
  // through iterators
  vector< vector<int> >::iterator itrow;
  vector<int>::iterator itcol;
  for (itrow = vM.begin(); itrow != vM.end(); itrow++) {
    for (itcol = itrow->begin(); itcol != itrow->end(); itcol++) {
      printf("%d\n", *itcol);
    }
  }
}