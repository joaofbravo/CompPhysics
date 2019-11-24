#ifndef __ELECTRON__
#define __ELECTRON__

#include "Particle.h"
#include "ElePosFunctor.h"

using std::list;

class Electron : public Particle {
public:
	Electron(const TVector3& mom =TVector3(), const TVector3& init =TVector3());
	Electron(const Electron&);
	~Electron();

	const Electron& operator=(const Electron&);

	static void SetSeed(unsigned int seed);
	static void SetElement(string Element);



	// Virtual inherited
	int GetType() const;
	double GetEnergy() const;
	list<Particle*> Interact(bool& del, Interactions&);
	
	void Print() const;
	void PrintFile(ofstream&) const;

private:
	// static double me; //mass
	static ElePosFunctor Func;
};

#endif