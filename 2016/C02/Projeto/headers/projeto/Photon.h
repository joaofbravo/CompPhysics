#ifndef __PHOTON__
#define __PHOTON__

#include "Particle.h"
#include "PhotonFunctor.h"

using std::list;

class Photon : public Particle {
public:
	Photon(const TVector3& mom =TVector3(), const TVector3& init =TVector3());
	Photon(const Photon&);
	~Photon();

	const Photon& operator=(const Photon&);

	static void SetSeed(unsigned int seed);
	static void SetElement(string element);


	// Virtual inherited
	int GetType() const;
	double GetEnergy() const;
	list<Particle*> Interact(bool& del, Interactions&);

	void Print() const;
	void PrintFile(ofstream&) const;

private:
	static PhotonFunctor Func;
};

#endif