#ifndef __FCrand__
#define __FCrand__

class FCrand {
public:
	FCrand(unsigned int=0);
	~FCrand();

	void SetSeed(unsigned int=0);
	unsigned int GetSeed() const;

	//generate one random between [min,max]
	float GetRandom(float=0., float=1.);
	//generate N randoms between [min,max]
	void GetRandoms(int, float*, float=0., float=1.);

private:
	unsigned int seed;
	unsigned int current;

	static const unsigned int a = 1103515245;
	static const unsigned int c = 12345;
	static const unsigned int m = 2147483648;
};

#endif

// To have a full period m for all seed values:
//  1) m and the offset c are relatively prime.
//  2) a-1 is divisible by all prime factors of m.
//  3) a-1 is divisible by 4 if m is divisible by 4.