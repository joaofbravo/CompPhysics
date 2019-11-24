#include "FCrand.h"
#include <ctime>
#include <iostream>

using namespace std;

FCrand::FCrand(unsigned int fseed) {
	if(fseed == 0){
		seed = time(0);
		current = seed;
	}
	else {
		seed = fseed;
		current = fseed;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

FCrand::~FCrand() {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void FCrand::SetSeed(unsigned int fseed) {
	if(fseed == 0){
		seed = time(0);
		current = seed;
	}
	else {
		seed = fseed;
		current = fseed;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

unsigned int FCrand::GetSeed() const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return seed;
}

float FCrand::GetRandom(float min, float max) {

	if(min > max){
		float c = min;
		min = max;
		max = c;
	}

	current = (a * current + c) % m;
	// cout << current << " ";

	float val = ((float)current / (float)(m-1)) * (max - min) + min;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return val;
}

void FCrand::GetRandoms(int N, float* arr, float min, float max) {

	if(min > max){
		float c = min;
		min = max;
		max = c;
	}

	for (int i = 0; i < N; ++i) {
		
		current = (a * current + c) % m;
		// cout << current << " ";

		arr[i] = ((float)current / (float)(m-1)) * (max - min) + min;	
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}