#include <iostream>

#include "simulator.h"
#include "velocityrule.h"

// fixes missing reference error in gcc builds
// see: http://stackoverflow.com/questions/329059/what-is-gxx-personality-v0-for/329195#329195
void *__gxx_personality_v0;

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
