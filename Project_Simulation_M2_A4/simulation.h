#ifndef SIMULATION_H_
#define SIMULATION_H_
#include "network.h"

class Simulation
{
public:
	explicit Simulation(Network* network);
	void StartSimulation(double time, double initial_phase_time);
	double GetSimulationTime();
private:
	Network* network_ = nullptr;
	double clock_{ 0 };
};
#endif
