#include <iostream>

#include "simulator.h"
#include "velocityrule.h"

int main()
{
    // testing simulator
	gga::Simulator simulator;
	simulator.AddSimulationRule<gga::VelocityRule>();

	for(int step=0; step < 100000; ++step){
		simulator.Step();
	}

    return 0;
}
