#pragma once

#include "CTRNN.h"

class Presatonta {
	public:
		// The constructor
		Presatonta(double ix = 0.0, double iy = 0.0)
		{
			Reset(ix,iy);
		};
		// The destructor
		~Presatonta() {};
		
		// Accessors
		double PositionX(void) {return x;};
		void SetPositionX(double newx) {x = newx;};
		double PositionY(void) {return y;};
		void SetPositionY(double newy) {y = newy;};
		
		// Control
    	void Reset(double ix, double iy);
    	void Step(double StepSize);
		double fRandy(double fMin , double fMax);
		double x, y, SL, SR, Sc, theta,alpha,width;
		double ex, ey;
};
