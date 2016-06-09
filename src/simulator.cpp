#include "simulator.h"

namespace gga {

    Simulator::Simulator() {

    }

    Simulator::~Simulator() {
        for(std::vector<SimulationRule*>::iterator moduleIter = mSimulationRules.begin();
            moduleIter != mSimulationRules.end();
            ++moduleIter)
        {
            delete *moduleIter;
        }
        mSimulationRules.clear();
    }

    void Simulator::Step() {
        for(std::vector<SimulationRule*>::iterator moduleIter = mSimulationRules.begin();
            moduleIter != mSimulationRules.end();
            ++moduleIter)
        {
            (*moduleIter)->Step(mUniverse);
        }
    }

}