#include "Presatonta.h"
#include "random.h"

// *******
// Control
// *******

void Presatonta::Reset(double ix, double iy)
{
	x = ix; y = iy; SR = 0.0; SL=0.0; theta=0.0; width=3-0;
}

double Presatonta::fRandy(double fMin, double fMax){
	double f = (double)rand()/RAND_MAX;
	return fMin + f * (fMax-fMin);
	}

void Presatonta::Step(double StepSize)
{	
	float xFut;
	float yFut;
	//Calculate the distance to the source of energy
	double distance = 1-sqrt(pow((x-ex),2)+pow(y-ey,2))/100;
	
	// Update the motors
	SL=fRandy(-10,10)*StepSize*5;
	SR=fRandy(-10,10)*StepSize*5;
	
	// Update the position
	Sc=(SL+SR)/2;
	alpha=(SR-SL)/width;
	
	theta=theta+alpha;
	x=x+Sc*cos(theta);
	y=y+Sc*sin(theta);
	/*xFut=x+Sc*cos(theta);
	yFut=y+Sc*sin(theta);
	if (xFut>=700){
		x=x+Sc*cos(-theta);
	} else{
		x = xFut;
	}
	if (yFut>=700){
		y=y+Sc*cos(-theta);
	} else{
		y = yFut;
	}*/
}
