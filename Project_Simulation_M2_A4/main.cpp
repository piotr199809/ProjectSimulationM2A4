#include <iostream>
#include "generator.h"
#include "package.h"
#include "transmitter.h"
#include "receiver.h"
#include "network.h"
#include "channel.h"
#include "simulation.h"

using namespace std;

int main(int argc, char* argv[])
{
	int max_simulation_time;
	int initial_phase_time;

	Network* network = new Network();
	Simulation simulation = Simulation(network);

	cout << "Enter max simulation time: ";
	cin >> max_simulation_time;

	cout << "Enter end time of initial phase: ";
	cin >> initial_phase_time;

	simulation.StartSimulation(max_simulation_time, initial_phase_time);
	
	return 0;
}