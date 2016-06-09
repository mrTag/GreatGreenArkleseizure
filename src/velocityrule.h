#ifndef VelocityRule_h__
#define VelocityRule_h__

namespace gga {

	class VelocityRule : public SimulationRule {

		virtual void Step(Universe& universe)
		{
			for(int particleIndex=0; particleIndex < universe.NumberOfParticles; ++particleIndex){
				universe.Particles[particleIndex].Position.X += universe.Particles[particleIndex].Velocity.X;
				universe.Particles[particleIndex].Position.Y += universe.Particles[particleIndex].Velocity.Y;
			}
		}

	};

}

#endif // VelocityRule_h__
