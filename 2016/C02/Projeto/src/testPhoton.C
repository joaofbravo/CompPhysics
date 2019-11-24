#include "Photon.h"
#include "cFCgraphics.h"
#include "TH1F.h"
#include <iostream>

using namespace std;

int main()
{
	TVector3 pi(0,0,0);
	TVector3 P(5000,0,0);

	Photon a (P,pi);
	a.SetSeed(0);
	bool del;
	vector<Particle*> all;

	vector<Particle*> result(a.Interact(del));
	all.insert(all.end(),result.begin(),result.end());

	for (int i = 0; i < all.size(); ++i)
	{
		all[i]->Print();
		cout << endl;
	}

}