#include "particle_emitter.hpp"
#include "raylib/raylib.h"
#include <climits>
#include <cmath>
#include <cstdlib>



float getRandomRange(float RangeX,float RangeY){
    std::srand((u32)(12345623 * sin(GetTime()*10))%INT_MAX);
    return RangeX + (float)rand()* (RangeY - RangeX) / RAND_MAX;
}



void ParticleEmitter::initParticlePool(){
    particlePoolSize = data.emissionRate * (data.particle_lifetime + 1);
    particlePool = new particle[particlePoolSize];
    nextAvailableParticle = &particlePool[0];
    for(i32 i=0; i < particlePoolSize-1; i++){
        particlePool[i].setNextParticle(&particlePool[i+1]);
    }
    particlePool[particlePoolSize - 1].setNextParticle(nullptr);
}

void ParticleEmitter::genParticle(){
    if(nextAvailableParticle == nullptr)
    {
        TraceLog(LOG_ERROR, "Particle Pool full");
        
        return;
    }
    particle* _particle = nextAvailableParticle;
    nextAvailableParticle = _particle->getNextParticle();


    float randAngle = getRandomRange(data.angleRange.x,data.angleRange.y);
    vec2 vel = vec2(cos(DEG2RAD * randAngle) * data.speed
                    ,-sin(DEG2RAD * randAngle) * data.speed); 
    // vel.print();
    _particle->initParticle(getTransform().pos,vel,&data);
    frames_since_last_gen = 0;
}

void ParticleEmitter::update(f32 delta){
    if(generate){
        f32 emmRate =  getRandomRange(data.emissionRate - data.emissionVariance , data.emissionRate); 
        if(frames_since_last_gen > GetFPS()/emmRate)
            genParticle();
    }
    

    for (int i = 0; i < particlePoolSize; i++)
    {
        if (particlePool[i].isAlive()){
            particlePool[i].update(delta);
        }
        else
        {
            particlePool[i].setNextParticle(nextAvailableParticle);
            nextAvailableParticle = &particlePool[i];
        }
    }

    frames_since_last_gen++;

}

void ParticleEmitter::draw(u32 layer){
    if(this -> layer == layer){
        for (int i = 0; i < particlePoolSize; i++){
            if (particlePool[i].isAlive()){
                particlePool[i].draw();
            }
        }
    }
}



ParticleEmitter::~ParticleEmitter(){
    delete[] particlePool;
}
