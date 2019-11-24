#include "cFCgraphics.h"
#include "TF1.h"
#include "TRandom.h"
#include "TGraph.h"

int main() {

  // open 3 canvas
  cFCgraphics G[3];

  // make three functions
  TF1 *f1 = new TF1("func1","sin(x)/x", 0., 10.);
  TF1 *f2 = new TF1("func2","cos(x)", 0., 10.);

  // make TGraph with 100 points
  TGraph *g1 = new TGraph(100); //100 points
  
  //  g1->SetName("g1");
  for (int i=0; i<100; i++) {
    g1->SetPoint(i,gRandom->Uniform(0.,10.), gRandom->Uniform(0.,10.));
  } 
  g1->SetMarkerStyle(20);

  // draw in one canvas (with only one pad) f1
  G[0].AddObject(f1);
  G[0].ListObjects();

  // draw in one canvas (with only one pad) f2
  G[1].AddObject(f2);
  G[1].ListObjects();

  // draw in one canvas (with only one pad) g1
  G[2].AddObject(g1);
  G[2].ListObjects();

  // draw all canvas
  G[0].Draw();
  G[1].Draw();
  G[2].Draw();
  
  // print plot to file
  G[0].Print("f1.pdf");
  G[1].Print("f2.pdf");
  G[2].Print("g1.pdf");

  return 0;
}