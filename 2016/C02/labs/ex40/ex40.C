#include <cmath>
#include <cstdio>

// Algo está mal...

void alg1(double,double,double&,double&);

void alg2(double,double,double&,double&);

int main()
{
  double x1, x2;
  double b = 0.03;
  double c = 0.0008;

  alg1 (b,c,x1,x2);
  printf("produto das duas soluções: sol=%lf; c=%lf\n", x1*x2, c);
  printf("algoritmo 1: x1=%.15lf; x2=%.15lf\n", x1, x2);

  alg2 (b,c,x1,x2);
  printf("algoritmo 2: x1=%.15lf; x2=%.15lf\n", x1, x2); 

  return 0;
}

void alg1 (double b, double c, double& x1, double& x2)
{
  x1 = b + sqrt(b*b - c);
  x2 = b - sqrt(b*b - c);
}

void alg2 (double b, double c, double& x1, double& x2)
{
  if (b>0){
    x1 = b + sqrt(b*b - c);
    x2 = c/x1;
  } else {
    x2 = b - sqrt(b*b - c);
    x1 = c/x2;
  }
}