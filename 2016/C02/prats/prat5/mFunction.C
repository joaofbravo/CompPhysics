#include "TF2.h"
#include "TROOT.h"
#include "TMath.h"
#include <cstdio>
#include <iostream>
using namespace std;

void mremove(TObject**);
void mFunction(int n=0);
void fpar(TF1*);

void mFunction(int n) {

  gROOT->Reset();

  printf("My first macro function...%d \n", n);

  // canvas
  TCanvas *c = new TCanvas("c", "My first canvas", 900, 600);
  c->Divide(2,1); // two pads equal size
  
  // manager
  TObject* m[100] = {NULL};

  //going to 1st pad
  c->cd(1);
  TF1 *f = new TF1("f", "sin(x)/x", 0., 20.);
  m[0] = f;
  double xmin, xmax;
  f->GetRange(xmin, xmax);
  cout << xmin << " " << xmax << endl;
  fpar(f);
  f->Draw();
  cout << "Hello" << endl;


  //going to 2nd pad
  c->cd(2);
  TF2 *f2 = new TF2("f2", "sin(x*y)/x*y", 0., TMath::TwoPi(), 0, TMath::TwoPi());
  f2->Draw();
  m[1] = f2;

  c->Update();

  getchar(); // espera por input do user para continuar prog
  
  mremove(m);

}


void fpar(TF1* f) {
  f->SetLineColor(kGreen+3);
  f->SetLineColor(kRed+3);
  f->SetLineStyle(2);
  f->SetLineWidth(6);
}


void mremove(TObject** a) {
  for (int i=0; i<100; i++) {
    printf("%p ",a[i]);
    if (a[i]) { 
      delete a[i];
    }
  }

}
