#include "cSUN.h"
#include "cFCgraphics.h"


int main () {

  cSUN S;

  // read magnetic field
  S.ReadFile("WSO_solar_magnetic_field_at_poles.txt", "B");

  // read number of sun spots
  S.ReadFile("SUN_spots_monthly.txt", "SPOTS");

  // read number of neutrons
  S.ReadFile("OULU_neutron_monitor_count.txt", "NM");

  // get magnetic field for an interval of time
  // time is defined as the number of days since 1 jan 1700
  // Ti: 01 april 1964
  // Tf: 01 january 2016

  string Ti = "1964 04 01";
  string Tf = "2016 01 01";

  TGraph* g1 = S.GetB(Ti, Tf);
  TGraph* g2 = S.GetSPOTS(Ti, Tf);
  TGraph* g3 = S.GetNM(Ti, Tf);

  // make plots
  cFCgraphics G[3];

  G[0].AddObject(g1);
  G[1].AddObject(g2);
  G[2].AddObject(g3);

  G[0].Draw();
  G[1].Draw();
  G[2].Draw();

  G[0].Print("B.pdf");
  G[1].Print("SPOTS.pdf");
  G[2].Print("NM.pdf");
  

  // save plots on files B.pdf, SPOTS.pdf, NM.pdf
  

  return 0;

}