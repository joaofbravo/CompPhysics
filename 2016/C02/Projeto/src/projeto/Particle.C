#include "Particle.h"
#include <iostream>

using namespace std;

TRandom3 Particle::R(0);


Particle::Particle(const TVector3& mom, const TVector3& init) : P(mom), pi(init), dist(0.) {

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Particle::Particle(const Particle& fp) : P(fp.P), pi(fp.pi), dist(fp.dist) {

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Particle::~Particle() {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

const Particle& Particle::operator=(const Particle& fp) {

	if (this != &fp){
		P = fp.P;
		pi = fp.pi;
		dist = fp.dist;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *this;
}

//=============== Set methods ===============

void Particle::SetParticle(const TVector3& mom, const TVector3& init) {
	P = mom;
	pi = init;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

void Particle::SetMomentum(const TVector3& mom) {
	P = mom;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Particle::SetOrigin(const TVector3& init) {
	pi = init;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

void Particle::SetDist(double fdist) {
	dist = fdist;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

void Particle::SetEnd(const TVector3& final) {

	dist = sqrt((pi.X()-final.X())*(pi.X()-final.X()) + 
				(pi.Y()-final.Y())*(pi.Y()-final.Y()) + 
				(pi.Z()-final.Z())*(pi.Z()-final.Z()));

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}


//=============== Get methods ===============

TVector3 Particle::GetMomentum() const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return P;
}

TVector3 Particle::GetOrigin() const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return pi;
}

double Particle::GetDist() const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return dist;
}

TVector3 Particle::GetEnd() const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	if (dist == 0.)
		return pi;
	return TVector3(pi + P*(dist/sqrt(P.X()*P.X() + P.Y()*P.Y() + P.Z()*P.Z())));
}

int Particle::GetSeed() const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	

	return R.GetSeed();
}

//=============== Print ===============

// 0 -> photon, 1 -> electron, 2 -> positron
void Particle::Print() const
{
	cout << pi.X() << " " << pi.Y() << " " << pi.Z() << "     ";
	cout << P.X() << " " << P.Y() << " " << P.Z() << "     ";
	cout << dist << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Particle::PrintFile(ofstream& F) const {

	F << pi.X() << " " << pi.Y() << " " << pi.Z() << "     ";
	F << P.X() << " " << P.Y() << " " << P.Z() << "     ";
	F << dist << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}