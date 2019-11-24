#ifndef __POSITRON__
#define __POSITRON__

#include "Particle.h"
#include "ElePosFunctor.h"
#include "PositronFunctor.h"


using std::list;

class Positron : public Particle {
public:
	Positron(const TVector3& mom =TVector3(), const TVector3& init =TVector3());
	Positron(const Positron&);
	~Positron();

	const Positron& operator=(const Positron&);

	static void SetSeed(unsigned int seed);
	static void SetElement(string Element);
	

	// Virtual inherited
	int GetType() const;
	double GetEnergy() const;
	list<Particle*> Interact(bool& del, Interactions&);
	
	
	void Print() const;
	void PrintFile(ofstream&) const;

private:
	static ElePosFunctor FuncElePos;
	static PositronFunctor FuncPos;
};

#endif