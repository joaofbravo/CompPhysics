#include "Photon.h"
#include "Electron.h"
#include "Positron.h"
#include "ParticleShower.h"
#include "TStyle.h"
#include <list>
#include <utility>
#include <iostream>

using namespace std;

const double me = 0.5109989461;
int ParticleShower::padcounter = -1;
int ParticleShower::histcounter = -1;

ParticleShower::ParticleShower(bool fprint, bool fdraw, bool fhist, bool ffile, string filename) : print(fprint), draw(fdraw), phist(fhist), file(ffile), filereading(false), file_name(filename), element("Aluminium") {

	gStyle->SetLegendBorderSize(0);

	if (file)
		F.open(filename);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ParticleShower::~ParticleShower() {
	for (list<Particle*>::iterator it = L_save.begin(); it != L_save.end(); ++it)
		delete *it;
	L_save.clear();

	for (vector<TLine*>::iterator it = line.begin(); it != line.end(); ++it)
		delete *it;
	line.clear();

	for (vector<TPolyLine3D*>::iterator it = line3d.begin(); it != line3d.end(); ++it)
		delete *it;
	line3d.clear();

	for (vector<TPaveText*>::iterator it = title.begin(); it != title.end(); ++it)
		delete *it;
	title.clear();

	for (vector<TLegend*>::iterator it = legend.begin(); it != legend.end(); ++it)
		delete *it;
	legend.clear();

	for (vector<TArrow*>::iterator it = arrow.begin(); it != arrow.end(); ++it)
		delete *it;
	arrow.clear();

	for (vector<TLatex*>::iterator it = text.begin(); it != text.end(); ++it)
		delete *it;
	text.clear();

	for (vector<TAxis3D*>::iterator it = axis3d.begin(); it != axis3d.end(); ++it)
		delete *it;
	axis3d.clear();

	for (vector<TH1F*>::iterator it = hist.begin(); it != hist.end(); ++it)
		delete *it;
	hist.clear();

	if (file)
		F.close();

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== Set Methods ===============

void ParticleShower::SetSeed(unsigned int seed) {
	Photon::SetSeed(seed);
	Electron::SetSeed(seed);
	Positron::SetSeed(seed);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::SetElement(string felement) {
	element = felement;

	Photon::SetElement(felement);
	Electron::SetElement(felement);
	Positron::SetElement(felement);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::SetPrint(bool fprint) {
	print = fprint;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::SetDraw(bool fdraw) {
	draw = fdraw;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::SetHist(bool fhist) {
	phist = fhist;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::SetFile(bool ffile) {
	file = ffile;

	if (file_name.empty()) {
		cout << endl << __PRETTY_FUNCTION__ << ": Error! No File input." << endl << endl;
		exit (1);
	}

	if (!F.is_open())
		F.open(file_name);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::AddParticle(const Particle& P) {

	type = P.GetType();

	if (type == 0)
		L_save.push_back(new Photon((Photon&)P));
	else if (type == 1)
		L_save.push_back(new Electron((Electron&)P));
	else if (type == 2)
		L_save.push_back(new Positron((Positron&)P));
	else {
		cout << __PRETTY_FUNCTION__ << ": No such particle in this simulation. ---> " << type << endl << endl;
		exit (1);
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::AddZPhoton(double energy) {
	L_save.push_back(new Photon(TVector3(0.,0.,energy), TVector3(0.,0.,0.)));

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::ResetList() {
	for (list<Particle*>::iterator it = L_save.begin(); it != L_save.end(); ++it)
		delete *it;
	L_save.clear();

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== Get Methods ===============

const int ParticleShower::size() const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return L_save.size();
}

//=============== Particle transportation ===============

vector<double> ParticleShower::Propagate(int x, int y, int z, string part) {

	list <Particle*> L;
	int q = 0;

	// List Copy
	for (list<Particle*>::iterator i = L_save.begin(); i != L_save.end(); ++i)
	{
		q++;
		type = (*i)->GetType();

		if (type == 0)
			L.push_back(new Photon((Photon&)**i));
		else if (type == 1)
			L.push_back(new Electron((Electron&)**i));
		else if (type == 2)
			L.push_back(new Positron((Positron&)**i));

		if (q == 1)
			Zorigin = ((*i)->GetOrigin())(2);
	}

	list <Particle*>::iterator it;
	bool del = false;
	Interactions inter = {0,0,0};
	PhotonN	= 0;
	ElePosN = 0;
	Swidth = 0.;

	TPad* pad;
	TPad* histpad[4];

	// Create Pad
	if (draw) {
		fcol=1.; ecol=1.; pcol=1.;
		xmin=-1.; ymin=-1.; zmin=-1.; xmax=1.; ymax=1.; zmax=1.;

		PadInit(part);
		pad = C.CreatePad(name.c_str());
	}

	// Create Hist Pads
	if (phist) {
		HistPadInit();
		histpad[0] = C.CreatePad(histname[0].c_str());
		histpad[1] = C.CreatePad(histname[1].c_str());
		histpad[2] = C.CreatePad(histname[2].c_str());
		histpad[3] = C.CreatePad(histname[3].c_str());
	}

	cout << endl;

	if (print)
		cout << "\n\nParticle: Type   pix piy piz   Px Py Pz   Distance" << endl << endl;

	// Particle shower creation
	while (!L.empty())
	{
		it = L.begin();

		L.splice(L.end(), (*it)->Interact(del, inter));

		if (!del)
			continue;

		type = (*it)->GetType();

		if (print || phist || file) {
			if (type == 0)
				PhotonN++;
			else
				ElePosN++;
		}

		if (print)
		{
			if (type == 0)
				cout << "Photon:   ";
			else if (type == 1)
				cout << "Electron: ";
			else
				cout << "Positron: ";

			(*it)->Print();
		}

		if (file)
			(*it)->PrintFile(F);

		if (draw)
		{
			if (z == -1)
				ParticleDump2D(**it, x, y);
			else
				ParticleDump3D(**it, x, y, z);
		}

		if (phist)
			HistGatherData(**it, x, y, z);

		delete *it;
		L.pop_front();
		del = false;
	}

	cout << endl;

	if (print) {
		cout << "Total Nº of Particles: " << PhotonN + ElePosN << endl;
		cout << "Nº of Photons: " << PhotonN << endl;
		cout << "Nº of Leptons: " << ElePosN << endl << endl;
		cout << "Nº of Photon Pair Production Events: " << inter.PairProduction << endl;
		cout << "Nº of Bremsstrahlung Radiation Events: " << inter.BremRad << endl;
		cout << "Nº of Electron-Positron Annihilation Events: " << inter.PosAnnihilation <<endl<<endl<<endl<<endl;
	}

	if (phist && q > 1)
		cout << "Particles' distribution histograms only work for 1 initial particle. Results might be bizarre with ===> " << q << " <=== particles.\n\n\n" << endl;

	// Pad Attributes
	if (draw) {
		if (z == -1)
			PadAtt2D(pad, x, y);
		else
			PadAtt3D(pad, x, y, z);
	}

	// Values for sampling:
	// - Zmax, Nmax, showers' length, width,
	// - nº of particles, nº of photons, nº of leptons,
	// - nº of PairProduction, nº of BremRadiation, nº of PositronAnnihilation

	vector<double> vec;

	// Create TH1Fs
	if (phist) {
		vec = HistDump(histpad, inter);

		vec.push_back(Allbin.size());
		vec.push_back(Swidth);
		vec.push_back(PhotonN + ElePosN);
		vec.push_back(PhotonN);
		vec.push_back(ElePosN);
		vec.push_back(inter.PairProduction);
		vec.push_back(inter.BremRad);
		vec.push_back(inter.PosAnnihilation);

		Allbin.clear();
		Photonbin.clear();
		ElePosbin.clear();
	}

	if (file) {
		F << PhotonN << " " << ElePosN << " " << Zorigin << " ";
		F << inter.PairProduction << " " << inter.BremRad << " " << inter.PosAnnihilation << " " << element;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return vec;
}

//=============== File Reader ===============

vector<double> ParticleShower::ReadFile(string filename, int x, int y, int z, string part) {

	if (!draw && !phist) {
		cout << endl << __PRETTY_FUNCTION__ << ": Error! Set drawing flags first." << endl << endl;
		exit (1);
	}

	if (filename.empty()) {
		cout << endl << __PRETTY_FUNCTION__ << ": Error! No File input." << endl << endl;
		exit (1);
	}

	ifstream iF (filename);

	if (!iF.is_open()) {
		cout << endl << __PRETTY_FUNCTION__ << ": Error! No file named -----> " << filename << endl << endl;
		exit (1);
	}

	// ========== Draw old shower from file ==========

	filereading = true;

	TPad* pad;
	TPad* histpad[4];

	// Create Pad
	if (draw) {
		fcol=1.; ecol=1.; pcol=1.;
		xmin=-1.; ymin=-1.; zmin=-1.; xmax=1.; ymax=1.; zmax=1.;

		PadInit(part);
		pad = C.CreatePad(name.c_str());
	}

	// Create Hist Pads
	if (phist) {
		HistPadInit();
		histpad[0] = C.CreatePad(histname[0].c_str());
		histpad[1] = C.CreatePad(histname[1].c_str());
		histpad[2] = C.CreatePad(histname[2].c_str());
		histpad[3] = C.CreatePad(histname[3].c_str());
	}

	// Info in file
	double xi, yi, zi;
	double px, py, pz;
	double dist;

	Photon P0;
	Electron P1;
	Positron P2;
	Interactions inter;
	Swidth = 0.;

	// Initial Photons
	iF >> type;
	while (type == 0)
	{
		iF >> xi >> yi >> zi >> px >> py >> pz >> dist;
		// cout << type << xi << yi << zi << px << py << pz << dist << endl;

		P0.SetParticle(TVector3(px, py, pz), TVector3(xi, yi, zi));
		P0.SetDist(dist);

		// Initial energies
		Eini.push_back(P0.GetEnergy());

		if (draw)
		{
			if (z == -1)
				ParticleDump2D(P0, x, y);
			else
				ParticleDump3D(P0, x, y, z);
		}

		if (phist)
			HistGatherData(P0, x, y, z);

		iF >> type;
	}

	// Rest of shower
	while (type == 0 || type == 1 || type == 2)
	{
		iF >> xi >> yi >> zi >> px >> py >> pz >> dist;
		// cout << type << " " << xi << " " << yi << " " << zi << " " << px << " " << py << " " << pz << " " << dist << endl;

		if (type == 0) {
			P0.SetParticle(TVector3(px, py, pz), TVector3(xi, yi, zi));
			P0.SetDist(dist);
		}
		else if (type == 1) {
			P1.SetParticle(TVector3(px, py, pz), TVector3(xi, yi, zi));
			P1.SetDist(dist);
		}
		else {
			P2.SetParticle(TVector3(px, py, pz), TVector3(xi, yi, zi));
			P2.SetDist(dist);
		}

		if (draw)
		{
			if (z == -1) {
				if (type == 0)
					ParticleDump2D(P0, x, y);
				else if (type == 1)
					ParticleDump2D(P1, x, y);
				else
					ParticleDump2D(P2, x, y);
			}
			else {
				if (type == 0)
					ParticleDump3D(P0, x, y, z);
				else if (type == 1)
					ParticleDump3D(P1, x, y, z);
				else
					ParticleDump3D(P2, x, y, z);
			}
		}

		if (phist) {
			if (type == 0)
				HistGatherData(P0, x, y, z);
			else if (type == 1)
				HistGatherData(P1, x, y, z);
			else
				HistGatherData(P2, x, y, z);
		}

		iF >> type;
	}

	if (phist) {
		if (Eini.size() > 1)
			cout << "Particles' distribution histograms only work for 1 initial particle. Results might be bizarre with ===> " << Eini.size() << " <=== particles.\n\n\n" << endl;

		PhotonN = type;
		iF >> ElePosN >> Zorigin >> inter.PairProduction >> inter.BremRad >> inter.PosAnnihilation >> element;
		// cout << PhotonN << " " << ElePosN << " " << Zorigin << " " << inter.PairProduction << " " << inter.BremRad << " " << inter.PosAnnihilation << " " << element << endl;
	}

	iF.close();

	// Pad Attributes
	if (draw) {
		if (z == -1)
			PadAtt2D(pad, x, y);
		else
			PadAtt3D(pad, x, y, z);
	}

	// Values for sampling:
	// - Zmax, Nmax, showers' length, width,
	// - nº of particles, nº of photons, nº of electrons,
	// - nº of PairProduction, nº of BremRadiation, nº of PositronAnnihilation

	vector<double> vec;

	// Create TH1Fs
	if (phist) {
		vec = HistDump(histpad, inter);

		vec.push_back(Allbin.size());
		vec.push_back(Swidth);
		vec.push_back(PhotonN + ElePosN);
		vec.push_back(PhotonN);
		vec.push_back(ElePosN);
		vec.push_back(inter.PairProduction);
		vec.push_back(inter.BremRad);
		vec.push_back(inter.PosAnnihilation);

		Allbin.clear();
		Photonbin.clear();
		ElePosbin.clear();
	}

	filereading = false;
	Eini.clear();
	
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return vec;
}

//=============== Draw and Save ===============

void ParticleShower::Draw() {

	if (!draw && !phist) {
		cout << __PRETTY_FUNCTION__ << ": Error! No Shower to draw." << endl << endl;
		exit (1);
	}

	// Draw created showers
	C.ListObjects();
	C.Draw();

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::Print(string filename) {

	if (!draw) {
		cout << __PRETTY_FUNCTION__ << ": Error! No Shower to save." << endl << endl;
		exit (1);
	}

	C.Print(filename);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== Drawing Methods ===============

void ParticleShower::PadInit(const string& part) {

	padcounter++;
	name = "pad" + std::to_string(padcounter);

	// Particles Transparency
	if (!part.empty()) {
		if (part == "photon") {
			ecol = 0.1;
			pcol = 0.1;
		}
		else if (part == "e-") {
			fcol = 0.1;
			pcol = 0.1;
		}
		else if (part == "e+") {
			fcol = 0.1;
			ecol = 0.1;
		}
		else {
			cout << __PRETTY_FUNCTION__ << ": No such particle in this simulation. ---> " << part << endl << endl;
			exit (1);
		}
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::ParticleDump2D(const Particle& P, const int& x, const int& y) {

	double xi, xf, yi, yf;

	xi = (P.GetOrigin())(x);
	yi = (P.GetOrigin())(y);
	xf = (P.GetEnd())(x);
	yf = (P.GetEnd())(y);

	if (xi < xmin)	xmin = xi; // xi
	if (xi > xmax)	xmax = xi;
	if (yi < ymin)	ymin = yi; // yi
	if (yi > ymax)	ymax = yi;
	if (xf < xmin)	xmin = xf; // xf
	if (xf > xmax)	xmax = xf;
	if (yf < ymin)	ymin = yf; // yf
	if (yf > ymax)	ymax = yf;

	line.push_back(new TLine(xi, yi, xf, yf));

	if (type == 0) {
		line[line.size()-1]->SetLineColorAlpha(kGreen-3, fcol);
		line[line.size()-1]->SetLineStyle(9);
		// line[line.size()-1]->SetLineWidth(1);
	}
	else if (type == 1) {
		line[line.size()-1]->SetLineColorAlpha(kBlue, ecol);
		// line[line.size()-1]->SetLineStyle(1);
		// line[line.size()-1]->SetLineWidth(1);
	}
	else {
		line[line.size()-1]->SetLineColorAlpha(kRed, pcol);
		// line[line.size()-1]->SetLineStyle(1);
		// line[line.size()-1]->SetLineWidth(1);
	}

	C.AddObject(line[line.size()-1], name.c_str());

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::ParticleDump3D(const Particle& P, const int& x, const int& y, const int& z) {

	double xi, xf, yi, yf, zi, zf;

	xi = (P.GetOrigin())(x);
	yi = (P.GetOrigin())(y);
	zi = (P.GetOrigin())(z);
	xf = (P.GetEnd())(x);
	yf = (P.GetEnd())(y);
	zf = (P.GetEnd())(z);

	if (xi < xmin)	xmin = xi; // xi
	if (xi > xmax)	xmax = xi;
	if (yi < ymin)	ymin = yi; // yi
	if (yi > ymax)	ymax = yi;
	if (xf < xmin)	xmin = xf; // xf
	if (xf > xmax)	xmax = xf;
	if (yf < ymin)	ymin = yf; // yf
	if (yf > ymax)	ymax = yf;
	if (zi < zmin)	zmin = zi; // zi
	if (zi > zmax)	zmax = zi;
	if (zf < zmin)	zmin = zf; // zf
	if (zf > zmax)	zmax = zf;

	line3d.push_back(new TPolyLine3D(2));
	line3d[line3d.size()-1]->SetPoint(0, xi, yi, zi);
	line3d[line3d.size()-1]->SetPoint(1, xf, yf, zf);

	if (type == 0) {
		line3d[line3d.size()-1]->SetLineColorAlpha(kGreen-3, fcol);
		line3d[line3d.size()-1]->SetLineStyle(9);
		// line3d[line3d.size()-1]->SetLineWidth(1);
	}
	else if (type == 1) {
		line3d[line3d.size()-1]->SetLineColorAlpha(kBlue, ecol);
		// line3d[line3d.size()-1]->SetLineStyle(1);
		// line3d[line3d.size()-1]->SetLineWidth(1);
	}
	else {
		line3d[line3d.size()-1]->SetLineColorAlpha(kRed, pcol);
		// line3d[line3d.size()-1]->SetLineStyle(1);
		// line3d[line3d.size()-1]->SetLineWidth(1);
	}

	C.AddObject(line3d[line3d.size()-1], name.c_str());

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::PadAtt2D(TPad* pad, const int& x, const int& y) {

	double yinc = ymax-ymin;
	double xinc = xmax-xmin;

	// Pad Range
	pad->Range(xmin-xinc/15, ymin-yinc/10, xmax+xinc/15, ymax+yinc/5);

	// X Axis Division (1 or 10 cm)
	double xx, yy, xxinc, yyinc;

	if (x != 2)
		xxinc = 1;
	else
		xxinc = 10;

	if (y != 2)
		yyinc = 1;
	else
		yyinc = 10;	

	for (xx = 0; xx > xmin; xx -= xxinc) {
		line.push_back(new TLine(xx, ymin-yinc/10, xx, ymax+yinc/5));
		line[line.size()-1]->SetVertical();
		line[line.size()-1]->SetLineStyle(3);
		line[line.size()-1]->SetLineColorAlpha(kBlack, 0.4);
		C.AddObject(line[line.size()-1], name.c_str());
	}

	for (xx = xxinc; xx < xmax; xx += xxinc) {
		line.push_back(new TLine(xx, ymin-yinc/10, xx, ymax+yinc/5));
		line[line.size()-1]->SetVertical();
		line[line.size()-1]->SetLineStyle(3);
		line[line.size()-1]->SetLineColorAlpha(kBlack, 0.4);
		C.AddObject(line[line.size()-1], name.c_str());
	}

	// Y Axis Division (1 or 10 cm)
	for (yy = yyinc; yy < ymax; yy += yyinc) {
		line.push_back(new TLine(xmin-xinc/15, yy, xmax+xinc/15, yy));
		line[line.size()-1]->SetHorizontal();
		line[line.size()-1]->SetLineStyle(3);
		line[line.size()-1]->SetLineColorAlpha(kBlack, 0.4);
		C.AddObject(line[line.size()-1], name.c_str());
	}

	for (yy = 0; yy > ymin; yy -= yyinc) {
		line.push_back(new TLine(xmin-xinc/15, yy, xmax+xinc/15, yy));
		line[line.size()-1]->SetHorizontal();
		line[line.size()-1]->SetLineStyle(3);
		line[line.size()-1]->SetLineColorAlpha(kBlack, 0.4);
		C.AddObject(line[line.size()-1], name.c_str());
	}

	// ========== Pad Top ==========

	// Title
	title.push_back(new TPaveText(xmin+xinc/5, ymax+yinc/11, xmin+xinc*4./5., ymax+0.18*yinc));
	title[title.size()-1]->AddText(("Electromagnetic Shower in " + element).c_str());
	C.AddObject(title[title.size()-1], name.c_str(), "");

	// Initial energies
	int j = 0;

	if (filereading)
	{
		for (vector<int>::iterator i = Eini.begin(); i != Eini.end(); ++i, ++j)
		{
			text.push_back(new TLatex(xmin-xinc/20, ymax+0.13*yinc-j*yinc/30, ("E#gamma " + std::to_string(j) + " = " + std::to_string(*i) + " MeV").c_str()));
			text[text.size()-1]->SetTextSize(0.02);
			C.AddObject(text[text.size()-1], name.c_str(), "");
		}
	}
	else
	{
		string Epart;

		for (list<Particle*>::iterator i = L_save.begin(); i != L_save.end(); ++i, ++j)
		{
			type = (*i)->GetType();

			if (type == 0)
				Epart = "E#gamma ";
			else if (type == 1)
				Epart = "Ee^{-} ";
			else if (type == 2)
				Epart = "Ee^{+} ";

			text.push_back(new TLatex(xmin-xinc/20, ymax+0.13*yinc-j*yinc/30, (Epart + std::to_string(j) + " = " + std::to_string((int)(*i)->GetEnergy()) + " MeV").c_str()));
			text[text.size()-1]->SetTextSize(0.02);
			C.AddObject(text[text.size()-1], name.c_str(), "");
		}
	}

	// Legend
	legend.push_back(new TLegend(0.88, 0.87, 0.99, 0.97));

	line.push_back(new TLine());
	line[line.size()-1]->SetLineColor(kGreen-3);
	line[line.size()-1]->SetLineStyle(9);
	legend[legend.size()-1]->AddEntry(line[line.size()-1], "  Photons", "l");

	line.push_back(new TLine());
	line[line.size()-1]->SetLineColor(kBlue);
	legend[legend.size()-1]->AddEntry(line[line.size()-1], "  Electrons", "l");

	line.push_back(new TLine());
	line[line.size()-1]->SetLineColor(kRed);
	legend[legend.size()-1]->AddEntry(line[line.size()-1], "  Positrons", "l");

	C.AddObject(legend[legend.size()-1], name.c_str());

	// ========== Pad Bottom ==========

	// Coordinate axes
	double xx2 = xmin-xinc/20;
	double yy2 = ymin-yinc/30;

	arrow.push_back(new TArrow(xx2, yy2, xmin+0.01*xinc, yy2, 0.01, "|>"));
	arrow[arrow.size()-1]->SetAngle(30);
	C.AddObject(arrow[arrow.size()-1], name.c_str(), "");

	arrow.push_back(new TArrow(xx2, yy2, xx2, ymin+yinc/15, 0.01, "|>"));
	arrow[arrow.size()-1]->SetAngle(30);
	C.AddObject(arrow[arrow.size()-1], name.c_str(), "");

	string ax, ay;
	if (x == 0)		 ax = "X";
	else if (x == 1) ax = "Y";
	else if (x == 2) ax = "Z";

	if (y == 0) 	 ay = "X";
	else if (y == 1) ay = "Y";
	else if (y == 2) ay = "Z";

	text.push_back(new TLatex(xmin+0.01*xinc, ymin-0.07*yinc, (ax + " [cm]").c_str()));
	text[text.size()-1]->SetTextSize(0.02);
	C.AddObject(text[text.size()-1], name.c_str(), "");

	text.push_back(new TLatex(xmin-xinc/15, ymin+yinc/13, (ay + " [cm]").c_str()));
	text[text.size()-1]->SetTextSize(0.02);
	C.AddObject(text[text.size()-1], name.c_str(), "");

	// X Scale
	xx -= xxinc;
	yy += yyinc;

	line.push_back(new TLine(xx-xxinc, yy, xx, yy)); // x middle _____
	line[line.size()-1]->SetHorizontal();
	line[line.size()-1]->SetLineColorAlpha(kBlack, 0.8);
	C.AddObject(line[line.size()-1], name.c_str());

	line.push_back(new TLine(xx-xxinc, yy-0.1, xx-xxinc, yy)); // x left |
	line[line.size()-1]->SetVertical();
	line[line.size()-1]->SetLineColorAlpha(kBlack, 0.8);
	C.AddObject(line[line.size()-1], name.c_str());

	line.push_back(new TLine(xx, yy-0.1, xx, yy)); // x right |
	line[line.size()-1]->SetVertical();
	line[line.size()-1]->SetLineColorAlpha(kBlack, 0.8);
	C.AddObject(line[line.size()-1], name.c_str());

	text.push_back(new TLatex(xx-xxinc/2., yy-0.05*yinc, std::to_string((int)xxinc).c_str()));
	text[text.size()-1]->SetTextSize(0.03);
	C.AddObject(text[text.size()-1], name.c_str(), "");

	// Y Scale
	line.push_back(new TLine(xx, yy, xx, yy+yyinc)); // y middle _____
	line[line.size()-1]->SetVertical();
	line[line.size()-1]->SetLineColorAlpha(kBlack, 0.8);
	C.AddObject(line[line.size()-1], name.c_str());

	line.push_back(new TLine(xx, yy, xx+0.1, yy)); // y lower |
	line[line.size()-1]->SetHorizontal();
	line[line.size()-1]->SetLineColorAlpha(kBlack, 0.8);
	C.AddObject(line[line.size()-1], name.c_str());

	line.push_back(new TLine(xx, yy+yyinc, xx+0.1, yy+yyinc)); // y upper |
	line[line.size()-1]->SetHorizontal();
	line[line.size()-1]->SetLineColorAlpha(kBlack, 0.8);
	C.AddObject(line[line.size()-1], name.c_str());

	text.push_back(new TLatex(xx+0.04*xinc, yy+yyinc/3., std::to_string((int)yyinc).c_str()));
	text[text.size()-1]->SetTextAngle(90);
	text[text.size()-1]->SetTextSize(0.03);
	C.AddObject(text[text.size()-1], name.c_str(), "");

	C.AddObject(pad);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::PadAtt3D(TPad* pad, const int& x, const int& y, const int& z) {

	// ========== Pad Top ==========

	// Title
	title.push_back(new TPaveText(0.24, 0.91, 0.76, 0.98, "NDC"));
	title[title.size()-1]->AddText(("Electromagnetic Shower in " + element).c_str());
	C.AddObject(title[title.size()-1], name.c_str(), "");

	// Initial energies
	int j = 0;

	if (filereading)
	{
		for (vector<int>::iterator i = Eini.begin(); i != Eini.end(); ++i, ++j)
		{
			text.push_back(new TLatex(0.03, 0.94-j*0.025, ("E#gamma " + std::to_string(j) + " = " + std::to_string(*i) + " MeV").c_str()));
			text[text.size()-1]->SetTextSize(0.02);
			text[text.size()-1]->SetNDC(kTRUE);
			C.AddObject(text[text.size()-1], name.c_str(), "");
		}
	}
	else
	{
		string Epart;

		for (list<Particle*>::iterator i = L_save.begin(); i != L_save.end(); ++i, ++j)
		{
			type = (*i)->GetType();

			if (type == 0)
				Epart = "E#gamma ";
			else if (type == 1)
				Epart = "Ee^{-} ";
			else if (type == 2)
				Epart = "Ee^{+} ";

			text.push_back(new TLatex(0.03, 0.94-j*0.025, (Epart + std::to_string(j) + " = " + std::to_string((int)(*i)->GetEnergy()) + " MeV").c_str()));
			text[text.size()-1]->SetTextSize(0.02);
			text[text.size()-1]->SetNDC(kTRUE);
			C.AddObject(text[text.size()-1], name.c_str(), "");
		}
	}

	// Legend
	legend.push_back(new TLegend(0.88, 0.87, 0.99, 0.97));

	line.push_back(new TLine());
	line[line.size()-1]->SetLineColor(kGreen-3);
	line[line.size()-1]->SetLineStyle(9);
	legend[legend.size()-1]->AddEntry(line[line.size()-1], "  Photons", "l");

	line.push_back(new TLine());
	line[line.size()-1]->SetLineColor(kBlue);
	legend[legend.size()-1]->AddEntry(line[line.size()-1], "  Electrons", "l");

	line.push_back(new TLine());
	line[line.size()-1]->SetLineColor(kRed);
	legend[legend.size()-1]->AddEntry(line[line.size()-1], "  Positrons", "l");

	C.AddObject(legend[legend.size()-1], name.c_str());

	// ========== Coordinate axes ==========

	axis3d.push_back(new TAxis3D());
	TAxis* Xaxis = axis3d[axis3d.size()-1]->GetXaxis();
	TAxis* Yaxis = axis3d[axis3d.size()-1]->GetYaxis();
	TAxis* Zaxis = axis3d[axis3d.size()-1]->GetZaxis();

	// Color
	Xaxis->SetAxisColor(kGray+3);
	Yaxis->SetAxisColor(kGray+3);
	Zaxis->SetAxisColor(kGray+3);

	Xaxis->SetLabelColor(kGray+2);
	Yaxis->SetLabelColor(kGray+2);
	Zaxis->SetLabelColor(kGray+2);

	// Range
	axis3d[axis3d.size()-1]->SetAxisRange(xmin, xmax, "X");
	axis3d[axis3d.size()-1]->SetAxisRange(ymin, ymax, "Y");
	axis3d[axis3d.size()-1]->SetAxisRange(zmin, zmax, "Z");

	// Axes Titles
	string ax, ay, az;

	if (x == 0)		 ax = "X";
	else if (x == 1) ax = "Y";
	else if (x == 2) ax = "Z";
	if (y == 0)		 ay = "X";
	else if (y == 1) ay = "Y";
	else if (y == 2) ay = "Z";
	if (z == 0)		 az = "X";
	else if (z == 1) az = "Y";
	else if (z == 2) az = "Z";

	axis3d[axis3d.size()-1]->SetXTitle((ax + " [cm]").c_str());
	axis3d[axis3d.size()-1]->SetYTitle((ay + " [cm]").c_str());
	axis3d[axis3d.size()-1]->SetZTitle((az + " [cm]").c_str());
	Xaxis->SetTitleOffset(1.6);
	Yaxis->SetTitleOffset(1.6);
	Zaxis->SetTitleOffset(1.6);

	C.AddObject(axis3d[axis3d.size()-1], name.c_str());

	// Yellow lines crossing zero
	line3d.push_back(new TPolyLine3D(2));
	line3d.push_back(new TPolyLine3D(2));

	if (x != 2) {
		line3d[line3d.size()-2]->SetPoint(0, xmin, 0, 0);
		line3d[line3d.size()-2]->SetPoint(1, xmax, 0, 0);

		if (z == 2) {
			line3d[line3d.size()-1]->SetPoint(0, 0, ymin, 0);
			line3d[line3d.size()-1]->SetPoint(1, 0, ymax, 0);
		}
		if (y == 2) {
			line3d[line3d.size()-1]->SetPoint(0, 0, 0, zmin);
			line3d[line3d.size()-1]->SetPoint(1, 0, 0, zmax);
		}
	}
	else {
		line3d[line3d.size()-2]->SetPoint(0, 0, ymin, 0);
		line3d[line3d.size()-2]->SetPoint(1, 0, ymax, 0);
		line3d[line3d.size()-1]->SetPoint(0, 0, 0, zmin);
		line3d[line3d.size()-1]->SetPoint(1, 0, 0, zmax);
	}

	line3d[line3d.size()-2]->SetLineColorAlpha(kYellow+1, 0.4);
	line3d[line3d.size()-1]->SetLineColorAlpha(kYellow+1, 0.4);
	line3d[line3d.size()-2]->SetLineStyle(7);
	line3d[line3d.size()-1]->SetLineStyle(7);
	C.AddObject(line3d[line3d.size()-2], name.c_str());
	C.AddObject(line3d[line3d.size()-1], name.c_str());

	C.AddObject(pad);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== Hist Methods ===============

void ParticleShower::HistPadInit() {

	padcounter++;
	histname[0] = "pad" + std::to_string(padcounter);

	padcounter++;
	histname[1] = "pad" + std::to_string(padcounter);

	padcounter++;
	histname[2] = "pad" + std::to_string(padcounter);

	padcounter++;
	histname[3] = "pad" + std::to_string(padcounter);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void ParticleShower::HistGatherData(const Particle& P, const int& x, const int& y, const int& z) {

	double xi, yi, xf, yf, zi, zf;

	xi = fabs((P.GetOrigin())(0));
	yi = fabs((P.GetOrigin())(1));
	xf = fabs((P.GetEnd())(0));
	yf = fabs((P.GetEnd())(1));
	zi = (P.GetOrigin())(2);
	zf = (P.GetEnd())(2);

	int origin = fabs(zi - Zorigin);
	int end = fabs(zf - Zorigin) + 1;

	while (Allbin.size() < end)
		Allbin.push_back(0);

	if (type == 0) {
		while (Photonbin.size() < end)
			Photonbin.push_back(0);
	}
	else {
		while (ElePosbin.size() < end)
			ElePosbin.push_back(0);
	}

	// Fill "bins"
	for (int i = origin; i < end; ++i) {
		Allbin[i]++;

		if (type == 0)
			Photonbin[i]++;
		else
			ElePosbin[i]++;
	}

	// Find shower's width
	double di = sqrt(xi*xi + yi*yi);
	double df = sqrt(xf*xf + yf*yf);

	if (di > Swidth)
		Swidth = di;
	if (df > Swidth)
		Swidth = df;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

vector<double> ParticleShower::HistDump(TPad** histpad, const Interactions& inter) {

	int allsize = Allbin.size();
	int photonsize = Photonbin.size();
	int elepossize = ElePosbin.size();
	int allentries = 0;
	int photonentries = 0;
	int eleposentries = 0;

	histcounter++;
	hist.push_back(new TH1F (("Particles " + std::to_string(histcounter)).c_str(), "Particles' Longitudinal Distribution;Z [cm];No Particles", allsize, 0., allsize));

	hist.push_back(new TH1F (("Photons " + std::to_string(histcounter)).c_str(), "Photons' Longitudinal Distribution;Z [cm];No Particles", photonsize, 0., photonsize));

	hist.push_back(new TH1F (("Leptons " + std::to_string(histcounter)).c_str(), "Leptons' Longitudinal Distribution;Z [cm];No Particles", elepossize, 0., elepossize));

	// Fill Hists and get Number of Particles
	for (int i = 0; i < allsize; ++i) {
		hist[hist.size()-3]->SetBinContent(i+1, Allbin[i]);
		allentries += Allbin[i];
	}

	for (int i = 0; i < photonsize; ++i) {
		hist[hist.size()-2]->SetBinContent(i+1, Photonbin[i]);
		photonentries += Photonbin[i];
	}

	for (int i = 0; i < elepossize; ++i) {
		hist[hist.size()-1]->SetBinContent(i+1, ElePosbin[i]);
		eleposentries += ElePosbin[i];
	}

	hist[hist.size()-3]->SetEntries(allentries);
	hist[hist.size()-2]->SetEntries(photonentries);
	hist[hist.size()-1]->SetEntries(eleposentries);

	// ZMax longitudinal profile and number of particles in Zmax
	int Zmax = hist[hist.size()-3]->GetMaximumBin();
	int Nmax = hist[hist.size()-3]->GetMaximum();

	C.AddObject(hist[hist.size()-3], histname[0].c_str());
	C.AddObject(hist[hist.size()-2], histname[1].c_str());
	C.AddObject(hist[hist.size()-1], histname[2].c_str());

	// ========== Pad with shower data ==========

	// Title
	title.push_back(new TPaveText(0.1, 0.84, 0.9, 0.99, "NDC"));
	title[title.size()-1]->AddText(("Electromagnetic Shower in " + element).c_str());

	if (filereading && Eini.size() != 0)
	{
		title[title.size()-1]->AddText(("Generated by a photon with Ei = " + std::to_string(Eini[0]) + " MeV").c_str());
	}
	else
	{
		type = (*L_save.begin())->GetType();
		string Part;

		if (type == 0)
			Part = "photon";
		else if (type == 1)
			Part = "electron";
		else if (type == 2)
			Part = "positron";

		title[title.size()-1]->AddText(("Generated by a " + Part + " with Ei = " + std::to_string((int)(*L_save.begin())->GetEnergy()) + " MeV").c_str());
	}
	C.AddObject(title[title.size()-1], histname[3].c_str(), "");

	// Number of Particles
	text.push_back(new TLatex(0.06, 0.7, ("Total No of Particles: " + std::to_string(PhotonN + ElePosN)).c_str()));
	text[text.size()-1]->SetTextSize(0.04);
	text[text.size()-1]->SetNDC(kTRUE);
	C.AddObject(text[text.size()-1], histname[3].c_str(), "");

	text.push_back(new TLatex(0.06, 0.65, ("No of Photons: " + std::to_string(PhotonN)).c_str()));
	text[text.size()-1]->SetTextSize(0.04);
	text[text.size()-1]->SetNDC(kTRUE);
	C.AddObject(text[text.size()-1], histname[3].c_str(), "");

	text.push_back(new TLatex(0.06, 0.6, ("No of Leptons: " + std::to_string(ElePosN)).c_str()));
	text[text.size()-1]->SetTextSize(0.04);
	text[text.size()-1]->SetNDC(kTRUE);
	C.AddObject(text[text.size()-1], histname[3].c_str(), "");

	// Number of Events
	text.push_back(new TLatex(0.06, 0.5, ("No of Photon Pair Production Events: " + std::to_string(inter.PairProduction)).c_str()));
	text[text.size()-1]->SetTextSize(0.04);
	text[text.size()-1]->SetNDC(kTRUE);
	C.AddObject(text[text.size()-1], histname[3].c_str(), "");

	text.push_back(new TLatex(0.06, 0.45, ("No of Bremsstrahlung Radiation Events: " + std::to_string(inter.BremRad)).c_str()));
	text[text.size()-1]->SetTextSize(0.04);
	text[text.size()-1]->SetNDC(kTRUE);
	C.AddObject(text[text.size()-1], histname[3].c_str(), "");

	text.push_back(new TLatex(0.06, 0.4, ("No of Electron-Positron Annihilation Events: " + std::to_string(inter.PosAnnihilation)).c_str()));
	text[text.size()-1]->SetTextSize(0.04);
	text[text.size()-1]->SetNDC(kTRUE);
	C.AddObject(text[text.size()-1], histname[3].c_str(), "");

	// Shower info
	text.push_back(new TLatex(0.06, 0.3, ("Max Longitudinal Profile at " + std::to_string(Zmax) + " cm with " + std::to_string(Nmax) + " particles").c_str()));
	text[text.size()-1]->SetTextSize(0.04);
	text[text.size()-1]->SetNDC(kTRUE);
	C.AddObject(text[text.size()-1], histname[3].c_str(), "");

	text.push_back(new TLatex(0.06, 0.25, ("Shower's Length: " + std::to_string(allsize) + " cm").c_str()));
	text[text.size()-1]->SetTextSize(0.04);
	text[text.size()-1]->SetNDC(kTRUE);
	C.AddObject(text[text.size()-1], histname[3].c_str(), "");

	text.push_back(new TLatex(0.06, 0.2, ("Shower's Width: " + std::to_string(Swidth) + " cm").c_str()));
	text[text.size()-1]->SetTextSize(0.04);
	text[text.size()-1]->SetNDC(kTRUE);
	C.AddObject(text[text.size()-1], histname[3].c_str(), "");

	C.AddObject(histpad[0]);
	C.AddObject(histpad[1]);
	C.AddObject(histpad[2]);
	C.AddObject(histpad[3]);

	// Values for sampling
	vector<double> vec;
	vec.push_back(Zmax);
	vec.push_back(Nmax);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return vec;
}