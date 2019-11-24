// F Barao (Fis Computacional IST 2015-16)
// Dep Fis

// to create an executable for this file
//
// make cFCgraphics object    : g++ -c cFCgraphics.C `root-config --cflags`
// make cFCgraphics static lib: ar ruv libFC.a cFCgraphics.o
// make executable            : g++ -o main.exe tgraphics.C -L FC/LIBS -lFC_x86_64 `root-config --cflags --libs`
// execute program            : ./main.exe     

#include "TF1.h"
#include "cFCgraphics.h"
#include "TAxis.h"

int main() {

  // instantiate the graphics class
  cFCgraphics G;

  // make three functions
  TF1 *f1 = new TF1("func","sin(x)/x", 0., 10.);
  TF1 *f2 = new TF1("func","cos(x)", 0., 10.);
  TF1 *f3 = new TF1("func","x*x", 0., 10.);

  // change line colors
  f1->SetLineColor(kRed);
  f2->SetLineColor(kBlue);
  f3->SetLineColor(kGreen);

  //change axis Y range of function f1
  f1->GetYaxis()->SetRangeUser(0.,2.);

  // make three pads
  TPad* pad1 = G.CreatePad("pad1");
  TPad* pad2 = G.CreatePad("pad2");
  TPad* pad3 = G.CreatePad("pad3");

  // add objects to pads
  G.AddObject(f1,"pad1");
  G.AddObject(f2,"pad1","same");
  G.AddObject(f3,"pad1","same");
  G.AddObject(f2,"pad2");
  G.AddObject(f3,"pad3");
  G.ListObjects();

  // add pads to canvas (graphics window)
  G.AddObject(pad1);
  G.AddObject(pad2);
  G.AddObject(pad3);

  // draw canvas
  G.Draw();

  // save graphics to file
  G.Print("a.png");
  G.Print("a.pdf");
  G.Print("a.eps");

  return 0;
}