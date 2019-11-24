#ifndef __FCMATRIXROTATION__
#define __FCMATRIXROTATION__

#include "FCmatrixFull.h"
#include "TVector3.h"

class FCmatrixRotation : public FCmatrixFull {
public:
	FCmatrixRotation(double theta, double phi); //theta-> ângulo com o eixo zz, phi-> ângulo em xy;
	FCmatrixRotation(const TVector3& zaxis);

	~FCmatrixRotation();

	TVector3 operator*(const TVector3&) const;
};

#endif