#ifndef universe_h__
#define universe_h__

#include <algorithm>
#include "vector2.h"

namespace gga {
    struct Particle {
        Vector2 Position;
        Vector2 Velocity;
		int Property;

		Particle() : Property(0) {}
    };

    struct Universe {
        Particle* Particles;
        int NumberOfParticles;

		Universe() :
			Particles(NULL), NumberOfParticles(0)
		{}

        void GrowUniverse(int newSize){
            Particle* temp = new Particle[newSize];
            if(Particles != NULL){
                std::copy(Particles, Particles + NumberOfParticles, temp);
            }
            delete[] Particles;
            Particles = temp;
        }
    };
}

#endif // universe_h__