// ***************************************************
// A very simple example program for the TSearch class
// ***************************************************

#include "TSearch.h"
#include "CTRNN.h"
#include "Agent.h"
#include <iostream>

//Global variables
int neurons=5;
double time=16;
double bias=16;
double gain=1;
double weight=16;

//Global constants
const double StepSize = 0.1;
const double RunDuration = 200;
const long RandomSeed = 1; 
const long simulations = 5;

// A simple 2D inverted quadratic evaluation function

void convertGentoPhen(TVector<double> &v, CTRNN &ctrnn){
	double paramValue;
	int paramIndex=1,nodeIndex,otherNodeIndex;
	ctrnn.SetCircuitSize(neurons);
	
	//Set time constants
	for(nodeIndex=1;nodeIndex<=neurons;nodeIndex++){
		paramValue=MapSearchParameter(v[paramIndex],0.1,time);
		ctrnn.SetNeuronTimeConstant(nodeIndex,paramValue);
		paramIndex++;
	}
	//Set bias
	for(nodeIndex=1;nodeIndex<=neurons;nodeIndex++){
		paramValue=MapSearchParameter(v[paramIndex],-bias,bias);
		ctrnn.SetNeuronBias(nodeIndex,paramValue);
		paramIndex++;
	}
	//Set gains
	/*for(nodeIndex=1;nodeIndex<=neurons;nodeIndex++){
		paramValue=MapSearchParameter(v[paramIndex],gain,gain);
		ctrnn.SetNeuronGain(nodeIndex,paramValue);
		paramIndex++;
	}*/
	for(nodeIndex=1;nodeIndex<=neurons;nodeIndex++){
		ctrnn.SetNeuronGain(nodeIndex,1.0);
	}
	//Set weights
	for(nodeIndex=1;nodeIndex<=neurons;nodeIndex++){
		for(otherNodeIndex=1;otherNodeIndex<=neurons;otherNodeIndex++){
			paramValue=MapSearchParameter(v[paramIndex],-weight,weight);
			ctrnn.SetConnectionWeight(nodeIndex,otherNodeIndex,paramValue);
			paramIndex++;
		}
	}
	
};	

double runSimulation(CTRNN ctrnn, long simulations){
	Agent dragon;
	Agent ball;
	double sum=0;
	int apunaladas;
	ifstream f;
  	//f.open("Nombresito.dat");
  	f.open("hapapa.dat");
	CTRNN redemierda;
  	f >> redemierda;
	ball.NervousSystem=ctrnn;
	dragon.NervousSystem = redemierda;
	for(int j=0;j<simulations;j++){
		ball.Reset(0, 0);
	    for (double time = 0; time < RunDuration; time += StepSize) {
	        dragon.Step(StepSize,ball.x,ball.y);
	        ball.Step(StepSize,dragon.x,dragon.y);
	        if ((ball.x < dragon.x+1 && ball.x>dragon.x-1)||(ball.y < dragon.y+1 && ball.y>dragon.y-1)){
	        	apunaladas++;
			}
	    } 
	    //sum+=(pow(2,apunaladas)-1)/(sqrt(pow(dragon.x-ball.x,2)+pow(dragon.y-ball.y,2))+1);
		sum+=(1/(sqrt(pow(dragon.x-ball.x,2)+pow(dragon.y-ball.y,2))+1));
	}
    return (sum/simulations)*apunaladas;
    //return 1/(sum/simulations);
}

double Evaluate(TVector<double> &v, RandomState &)
{
	double fit;
	CTRNN ctrnn;
	convertGentoPhen(v,ctrnn);
	for(int i=1;i<=neurons;i++){
		ctrnn.SetNeuronState(i,0);
	}
	fit=runSimulation(ctrnn,simulations);
	return fit;
}
// The main program

int main (int argc, const char* argv[]) {
	
  ifstream f;
  //f.open("Nombresito.dat");
  f.open("hapapa.dat");
  TSearch s(neurons*(2+neurons));
  CTRNN redemierda;
  f >> redemierda;
  
  // Configure the search
  
  s.SetRandomSeed(87632455);
  s.SetEvaluationFunction(Evaluate);
  s.SetSelectionMode(RANK_BASED);
  s.SetReproductionMode(HILL_CLIMBING);
  s.SetPopulationSize(100);
  s.SetMaxGenerations(100);
  s.SetMutationVariance(0.7);
  s.SetCrossoverProbability(0.7);
  s.SetCrossoverMode(UNIFORM);
  s.SetMaxExpectedOffspring(1.1);
  s.SetElitistFraction(0.1);
  s.SetReEvaluationFlag(1);
    
  // Run the search
  s.ExecuteSearch();
  
  // Display the best individual found
  cout << s.BestIndividual() << endl;
  ofstream ofs;
  ofs.open("data.csv");
  Agent ball, agentemierda;
  CTRNN ctrnn;
  convertGentoPhen(s.BestIndividual(),ctrnn);
  ball.NervousSystem=ctrnn;
  ball.Reset(0, 0);
  agentemierda.NervousSystem = redemierda;
  agentemierda.Reset(20.0,20.0);

  for (double time = 0; time < RunDuration; time += StepSize) {
  	agentemierda.Step(StepSize,ball.x,ball.y);
	ball.Step(StepSize,agentemierda.x,agentemierda.y);
  	ofs<<ball.x<<","<<ball.y<<","<<agentemierda.x<<","<<agentemierda.y<<endl;
  }
  
  ofs.close();
  
  //ofs.open("hapapa.dat");
  ofs.open("Nombresito.dat");
  ofs<<ctrnn;
  ofs.close();
  return 0;
}
