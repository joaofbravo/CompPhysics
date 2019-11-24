#include "FCrand.h"
#include <iostream>
#include <cmath>

using namespace std;

int main() {

	FCrand R;

	cout << "10 GetRandom test:" << endl;
	for (int i = 0; i < 10; ++i)
		cout << R.GetRandom() << endl;

	int seed1 = R.GetSeed();
	cout << "\nR seed = " << seed1 << endl;

	float a = R.GetRandom();
	float b = R.GetRandom(30, 30.09);
	cout << "\na: " << a << "\t" << "b: " << b << endl << endl;

	FCrand R2(33);
	R2.SetSeed(2);
	for (int i = 0; i < 5; ++i)
		cout << "R: " << R.GetRandom() << "\t" << "R2: " << R2.GetRandom() << endl;

	float arr[10];
	R.GetRandoms(10, arr);
	cout << "\n10 GetRandoms test:" << endl;
	for (int i = 0; i < 10; ++i)
		cout << arr[i] << endl;

	R.GetRandoms(10, arr, 93.2, 90);
	cout << "\n10 GetRandoms test:" << endl;
	for (int i = 0; i < 10; ++i)
		cout << arr[i] << endl;

	float arr2[1000000];
	R.GetRandoms(1000000, arr2);

	float avg = 0.;
	for (int i = 0; i < 1000000; ++i)
		avg += arr2[i];
	avg /= 1000000;
	cout << "\nValor médio: " << avg << endl;

	float stddeviation = 0.;
	for (int i = 0; i < 1000000; ++i)
		stddeviation += (arr2[i]-avg)*(arr2[i]-avg);
	stddeviation = sqrt(stddeviation/999999);
	cout << "Desvio padrão: " << stddeviation << endl;

	return 0;
}