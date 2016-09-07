#include <iostream>
#include <stdio.h>

#include "simulator.h"
#include "velocityrule.h"
#include "GL\freeglut.h"

// fixes missing reference error in gcc builds
// see: http://stackoverflow.com/questions/329059/what-is-gxx-personality-v0-for/329195#329195
void *__gxx_personality_v0;

int main(int argc, char* argv[])
{
	// init GLUT and create window
	// glutInit(&argc, argv);

	// register callbacks

	// enter GLUT event processing cycle


    // testing simulator
	gga::Simulator simulator;
	simulator.AddSimulationRule<gga::VelocityRule>();

	for(int step=0; step < 100000; ++step){
		simulator.Step();
	}

    return 0;
}