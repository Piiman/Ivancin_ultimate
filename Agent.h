#pragma once

#include "CTRNN.h"

class Agent {
	public:
		// The constructor
		Agent(double ix = 0.0, double iy = 0.0, double EX=0,double EY=0)
		{
			Reset(ix,iy);
		};
		// The destructor
		~Agent() {};
		
		// Accessors
		double PositionX(void) {return x;};
		void SetPositionX(double newx) {x = newx;};
		double PositionY(void) {return y;};
		void SetPositionY(double newy) {y = newy;};
		
		// Control
    	void Reset(double ix, double iy);
    	void Step(double StepSize, double cazX, double cazY);
		
		double x, y, SL, SR, Sc, theta,alpha,width;
		double ex, ey;
		CTRNN NervousSystem;
};
