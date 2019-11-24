#include "cSUN.h"
#include "cFCgraphics.h"
#include "TF1.h"
#include "TH1D.h"
#include <cmath>

using namespace std;

int main () {

  cSUN S;

  // read magnetic field
  S.ReadFile("WSO_solar_magnetic_field_at_poles.txt", "B");

  // read number of sun spots
  S.ReadFile("SUN_spots_monthly.txt", "SPOTS");

  // read number of neutrons
  S.ReadFile("OULU_neutron_monitor_count.txt", "NM");

  vector<sB> vB;
  vector<sSPOTS> vSPOTS;
  vector<sNM> vNM;
  S.GetB(vB);
  S.GetSunSpots(vSPOTS);
  S.GetMonitorCounts(vNM);

  // Graphs
  TF1 *f1 = new TF1("func1", "[0] + [1]*sin([2]*x-[3])", 96000., 116000.);
  f1->SetParameter(0, 100);
  f1->SetParameter(1, 10.);
  f1->SetParameter(2, 0.001256637);
  f1->SetParameter(3, 10.);

  TF1 *f2 = new TF1("func2", "[0] + [1]*sin([2]*x-[3])", 96000., 116000.);
  f2->SetParameter(0, 6000);
  f2->SetParameter(1, 10.);
  f2->SetParameter(2, 0.001256637);
  f2->SetParameter(3, 10.);

  TGraph* g1 = S.GetSPOTS("1749 01 01", "2016 09 01");
  g1->Fit(f1, "L");

  TGraph* g2 = S.GetNM("1964 04 01", "2016 09 01");
  g2->Fit(f2, "L");

  // Hists
  TH1D* hist1 = new TH1D ("hist1", "Sun Spots Diference Modules", 200, 0., 320.);

  for (int i = 0; i < vSPOTS.size(); i++){
    hist1->Fill(fabs(vSPOTS[i].n - f1->Eval(vSPOTS[i].time)));
    // cout << vSPOTS[i].n << "    " << f1->Eval(vSPOTS[i].time) << endl;
  } 

  TH1D* hist2 = new TH1D ("hist2", "Neutron Monitor Count Diference Modules", 250, 0., 1000.);

  for (int i = 0; i < vNM.size(); i++){
    hist2->Fill(fabs(vNM[i].n - f2->Eval(vNM[i].time)));
    // cout << vNM[i].n << "    " << f2->Eval(vNM[i].time) << endl;
  }

  // make plots
  cFCgraphics G[4];

  G[0].AddObject(g1);
  G[1].AddObject(g2);
  G[2].AddObject(hist1);
  G[3].AddObject(hist2);
  
  G[0].Draw();
  G[1].Draw();
  G[2].Draw();
  G[3].Draw();
  
  // save plots on files B.pdf, SPOTS.pdf, NM.pdf
  G[0].Print("SPOTS_fit.pdf");
  G[1].Print("NM_fit.pdf");
  G[2].Print("diferencas_SPOTS.pdf");
  G[3].Print("diferencas_NM.pdf");

  return 0;  
}