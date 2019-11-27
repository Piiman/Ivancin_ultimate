#include "Agent.h"
#include "random.h"

// *******
// Control
// *******

void Agent::Reset(double ix, double iy,double newex,double newey)
{
	x = ix; y = iy; SR = 0.0; SL=0.0; theta=0.0; width=3-0;
	ex=newex; ey=newey;
	NervousSystem.RandomizeCircuitState(-0.1,0.1);
}

void Agent::Step(double StepSize, double newex,double newey)
{
	float xFut;
	float yFut;
	//Calculate the distance to the source of energy
	ex=newex; ey=newey;
	double distance = 1-sqrt(pow((x-ex),2)+pow(y-ey,2))/100;
	
	//Feed the neuron with the distance
	NervousSystem.SetNeuronExternalInput(1,distance);
	
	//Integrate the neural network
	NervousSystem.EulerStep(StepSize);
	
	// Update the motors
	SL=NervousSystem.NeuronOutput(1)*StepSize*5;
	SR=NervousSystem.NeuronOutput(2)*StepSize*5;
	
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
