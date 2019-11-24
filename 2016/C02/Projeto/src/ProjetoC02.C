#include "Photon.h"
#include "Electron.h"
#include "Positron.h"
#include "ParticleShower.h"
#include "TRandom3.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TPad.h"
#include <fstream>

using namespace std;

int main() {

	ParticleShower Shower(false, false, true, false, "data/EMShower.txt");

	// Shower.SetSeed(1000);

	// First Photon
	Shower.AddZPhoton(5000.);
	Shower.Propagate(0, 2); // (x=0, y=1, z=2)
	Shower.ResetList();
	Shower.AddZPhoton(2000.);
	Shower.Propagate(0, 2); // (x=0, y=1, z=2)
	Shower.ResetList();
	Shower.AddZPhoton(1000.);
	Shower.Propagate(0, 2); // (x=0, y=1, z=2)

	Shower.Draw();
	Shower.Print("data/classic.pdf");



	return 0;
}