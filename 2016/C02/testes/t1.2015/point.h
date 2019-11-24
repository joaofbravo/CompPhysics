#ifndef __point__
#define __point__

class point {
public:
	point(float=0., float=0.);
	point(const point&);
	~point();

	const point& operator= (const point&);
	point operator+(const point&);
	point operator-(const point&);
	point operator*(const point&);
	float operator!();

	void Print();

private:
	float* coo; //point coordinates 
};                                                                                                                                                                                                    
#endif