#ifndef __PARTICLESHOWER__
#define __PARTICLESHOWER__

#include "cFCgraphics.h"
#include "TPad.h"
#include "TLine.h"
#include "TPolyLine3D.h"

#include "TPaveText.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "TAxis3D.h"

#include "TH1F.h"

#include "Particle.h"
#include <list>
#include <string>
#include <fstream>

using std::list;
using std::string;

class ParticleShower {
public:
	// Flags:
	// print -> print info in bash;
	// draw -> draw shower in 2D or 3D
	// hist -> draw info in TH1F (assuming propagation in zz direction)
	// file, filename -> save info in filename;

	ParticleShower(bool fprint =true, bool fdraw =false, bool fhist =false, bool ffile =false, string filename ="data/ParticleShower.txt");
	~ParticleShower();

	// Set methods
	void SetSeed(unsigned int seed);
	void SetElement(string felement);
	
	void SetPrint(bool);
	void SetDraw(bool);
	void SetHist(bool);
	void SetFile(bool);

	void AddParticle(const Particle&);
	void AddZPhoton(double energy); // add photon in origin with Pz=E=energy
	void ResetList();

	// Get methods
	const int size() const;

	// Particle transportation:
	// - get 2D (x,y) or 3D (x,y,z) shower representation (x=0, y=1, z=2)
	// - part = "photon", "e-", "e+" to emphasize those particles' path in output
	// - returns vector with general data for sampling
	vector<double> Propagate(int x=0, int y=2, int z=-1, string part ="");

	// File Reader: same options of Propagate
	vector<double> ReadFile(string filename, int x=0, int y=2, int z=-1, string part ="");

	void Draw();
	void Print(string filename ="data/ParticleShower.pdf");

private:
	list <Particle*> L_save;

	// Flags
	bool print;
	bool draw;
	bool phist;
	bool file;
	bool filereading; // while reading file
	ofstream F;
	string file_name;

	// Drawing methods
	void PadInit(const string& part);
	void ParticleDump2D(const Particle& P, const int& x, const int& y);
	void ParticleDump3D(const Particle& P, const int& x, const int& y, const int& z);
	void PadAtt2D(TPad* pad, const int& x, const int& y);
	void PadAtt3D(TPad* pad, const int& x, const int& y, const int& z);

	// Hist methods
	void HistPadInit();
	void HistGatherData(const Particle&, const int& x, const int& y, const int& z);
	vector<double> HistDump(TPad**, const Interactions&);

	// Drawing objects
	cFCgraphics C;
	vector<TLine*> line;
	vector<TPolyLine3D*> line3d;
	vector<TPaveText*> title;
	vector<TLegend*> legend;
	vector<TArrow*> arrow;
	vector<TLatex*> text;
	vector<TAxis3D*> axis3d;
	vector<TH1F*> hist;

	static int padcounter;
	string name; // Pad name
	double xmin, ymin, zmin, xmax, ymax, zmax; // Pad Range
	float fcol, ecol, pcol; // Particles Transparency
	int type; // Particle type
	int PhotonN, ElePosN; // Particle number
	string element; // medium element

	// Hist objects
	static int histcounter;
	string histname[4]; // Hist pad names
	double Zorigin; // Shower zz origin
	double Swidth; // Shower xy width
	vector<int> Eini; // File's initial energies
	vector<int> Allbin; // 1cm hist bins
	vector<int> Photonbin;
	vector<int> ElePosbin;
};

#endif