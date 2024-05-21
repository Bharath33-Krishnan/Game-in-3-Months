#include "particle_data.hpp"
#include "../core/scene.hpp"
#include "particle.hpp"



class ParticleEmitter:public Core::AbstractEntity{
private:
    particle* nextAvailableParticle;
    particle* particlePool;
    i32 particlePoolSize;
    i32 frames_since_last_gen;

    bool generate = true;

protected:
    Core::Scene* scene;
    particleEmitterData data;

public:
    void initParticlePool();// Call After init function 
    void update(f32 delta)override;
    void draw(u32 layer)override;
    void updateData(particleEmitterData data){this->data = data;};
    void genParticle();
    inline particleEmitterData getData(){return data;};
    ~ParticleEmitter();
};
