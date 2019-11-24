#include "Agent.h"
#include "random.h"

// *******
// Control
// *******

void Agent::Reset(double ix, double iy)
{
	x = ix; y = iy; SR = 0.0; SL=0.0; theta=0.0; width=3-0;
	NervousSystem.RandomizeCircuitState(-0.1,0.1);
}

double xFut,yFut;

void Agent::Step(double StepSize, double cazX, double cazY)
{
	//Calculate the distance to the source of energy
	ex=cazX; ey=cazY;
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
	if(xFut<700&&xFut>0){
		x = xFut;
	}
	if(yFut<700&&yFut>0){
		y = yFut;
	}*/
}
