#ifndef __Motion1D__
#define __Motion1D__

class Motion1D {
public:
	Motion1D(int=0);
	virtual ~Motion1D();

	void SetMotion(int, float*, float*);

	int GetN();
	float* GetTimes();
	float* GetPositions();

	virtual void Print();
	float TotalDistance();
	float MeanVelocity();

protected:
	int N; //number of points
	float* t; //time array
	float* x; //position array
};

inline void swap(float*, int, int);
void selectsort2v(int, float*, float*);

#endif