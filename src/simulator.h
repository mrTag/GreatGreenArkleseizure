#ifndef simulator_h__
#define simulator_h__

#include <vector>
#include "universe.h"

namespace gga {
    class SimulationRule {
        public:
        virtual void Step(Universe& universe) = 0;
        virtual ~SimulationRule() {}
    };

    class Simulator {
        Universe mUniverse;
        std::vector<SimulationRule*> mSimulationRules;

        public:
        Simulator();
        ~Simulator();

        template<typename SimRuleClass> 
        SimRuleClass* AddSimulationRule(){
			SimRuleClass* simRuleObj = new SimModClass();
            mSimulationRules.push_back(simRuleObj);
			return simRuleObj;
        }

        void Step();
    };
}

#endif // simulator_h__
