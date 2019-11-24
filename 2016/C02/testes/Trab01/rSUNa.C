#include "cSUN.h"

using namespace std;

int main () {

  cSUN S;

  // read physical observables: B, SPOTS and Neutron monitors
  // The second argument of the ReadFile method allows to distinguish the different file formats
  // to read

  // read magnetic field
  S.ReadFile("WSO_solar_magnetic_field_at_poles.txt", "B");

  // read number of sun spots
  S.ReadFile("SUN_spots_monthly.txt", "SPOTS");

  // read number of neutrons
  S.ReadFile("OULU_neutron_monitor_count.txt", "NM");

  // get all measurements
  vector<sB> vB;
  vector<sSPOTS> vSPOTS;
  vector<sNM> vNM;
  S.GetB(vB);
  S.GetSunSpots(vSPOTS);
  S.GetMonitorCounts(vNM);

  // print values to screen
  vector<sB>::iterator itB = vB.begin();
  vector<sSPOTS>::iterator itSPOTS = vSPOTS.begin();
  vector<sNM>::iterator itNM = vNM.begin();
  printf(" time(B)    B  | time(SPOTS) SPOTS | time(NM)   NM\n");
  while ( itB != vB.end() && itSPOTS != vSPOTS.end() && itNM != vNM.end() ) {
    printf( "%7.2f %8.2f  %7.2f %8.2f  %7.2f %8.2f \n",
     (*itB).time, (*itB).b,  (*itSPOTS).time, (*itSPOTS).n,  (*itNM).time, (*itNM).n
     );
    itB++;
    itSPOTS++;
    itNM++;
  }

  // end
  return 0;
}