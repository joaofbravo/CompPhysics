#ifndef __PARTICLE__
#define __PARTICLE__

#include "TVector3.h"
#include "TRandom3.h"
#include <string>
#include <list>
#include <fstream>

using std::string;
using std::list;

struct Interactions {
	int PairProduction;
	int BremRad;
	int PosAnnihilation;
};

class Particle {
public:
	Particle(const TVector3& mom =TVector3(), const TVector3& init =TVector3());
	Particle(const Particle&);
	virtual ~Particle();

	const Particle& operator=(const Particle&);

	// Set methods
	void SetParticle(const TVector3& mom, const TVector3& init);
	void SetMomentum(const TVector3&);
	void SetOrigin(const TVector3&);
	void SetDist(double);
	void SetEnd(const TVector3&);

	// Get methods
	virtual int GetType() const = 0; // 0 -> photon, 1 -> electron, 2 -> positron
	TVector3 GetMomentum() const;
	virtual double GetEnergy() const = 0;
	TVector3 GetOrigin() const;
	double GetDist() const;
	TVector3 GetEnd() const;

	int GetSeed() const;

	virtual list<Particle*> Interact(bool& del, Interactions&) = 0;

	// Print
	virtual void Print() const;
	virtual void PrintFile(ofstream&) const;

protected:
	static TRandom3 R;

	TVector3 P; //linear momentum
	TVector3 pi; //origin
	double dist; //distance to end

};

#endif