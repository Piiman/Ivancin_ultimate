// ***************************************************
// A very simple example program for the TSearch class
// ***************************************************

#include "TSearch.h"
#include "CTRNN.h"
#include "Agent.h"
#include "Presatonta.h"

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

double fRand(double fMin , double fMax){
	double f = (double)rand()/RAND_MAX;
	return fMin + f * (fMax-fMin);
}

double runSimulation(CTRNN ctrnn,long simulations){
	Agent ball;
	Presatonta tonto;  
	double sum=0;
	ball.NervousSystem=ctrnn;
	for(int j=0;j<simulations;j++){
		double cordx = fRand(-30, 30);
		double cordy = fRand(-30, 30);
		tonto.Reset(cordx,cordy);
		ball.Reset(0, 0, tonto.x, tonto.y);
	    for (double time = 0; time < RunDuration; time += StepSize) {
	        ball.Step(StepSize, tonto.x, tonto.y);
	        tonto.Step(StepSize);
	    } 
	    sum+=1/(sqrt(pow(ball.ex-ball.x,2)+pow(ball.ey-ball.y,2))+1);
	}
    return sum/simulations;
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
  TSearch s(neurons*(2+neurons));
    
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
  Agent ball;
  Presatonta tonto;
  CTRNN ctrnn;
  convertGentoPhen(s.BestIndividual(),ctrnn);
  ball.NervousSystem=ctrnn;
  tonto.Reset(20,-20);
  ball.Reset(0, 0, tonto.x, tonto.y);
  for (double time = 0; time < RunDuration; time += StepSize) {
  	ball.Step(StepSize, 14, -16);
  	tonto.Step(StepSize);
  	ofs<<ball.x<<","<<ball.y<<","<<tonto.x<<","<<tonto.y<<endl;
  }
  ofs.close();
  ofs.open("Nombresito.dat");
  ofs<<ctrnn;
  ofs.close();
  
  
  return 0;
}
