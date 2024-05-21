#include "particle_emitter.hpp"


void lerp(f32 start,f32 stop,f32 t){

}

ParticleEmitter::ParticleEmitter(particleEmitterData data){
    particlePoolSize = data.emissionRate * (data.particle_lifetime + 1);
    particlePool = new particle[particlePoolSize];
    for(i32 i=0; i < particlePoolSize-1; i++){
        particlePool[i].setNextParticle(&particlePool[i+1]);
    }
    this->data = data;
}

ParticleEmitter::~ParticleEmitter(){
    delete[] particlePool;
}
