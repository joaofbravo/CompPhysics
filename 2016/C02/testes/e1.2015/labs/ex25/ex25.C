#include "Box.h"

using namespace std;

int main() {
	// criar dois cubos de lado 1
	Box B1;
	Box B2 = B1;
	
	// somar dois cubos
	Box B3 = B1 + B2;
	
	// criar dois paralelipipedos
	Box B4(1,1,2);
	Box B5(B4);
	
	// somar os dois paralelipipedos
	Box B6;
	B6 = B4 + B5;

	// calcular volumes
	float volume_2 = B2.GetVolume();
	float volume_6 = B6.GetVolume();

	cout << "volumes: " << volume_2 << " " << volume_6 << endl;

	// criar Box por ponteiro
	Box* pB7 = new Box();
	Box* pB8 = new Box();
	Box* pBresult = pB7->Add_pB(pB8);

	float volume_pBresult = pBresult->GetVolume();
	cout << "volume: " << volume_pBresult << endl;

	delete pB7;
	delete pB8;
	delete pBresult;

	return 0;
}