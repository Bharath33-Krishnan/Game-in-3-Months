#include "particle.hpp"
#include "particle_emitter.hpp"
#include "raylib/raylib.h"

template <typename T>
T lerp(T start, T stop, float t){
    return start*std::max((1.f - t),0.f)+stop*std::min(1.f,t);
}

Vector4 vec4lerp(Vector4 start ,Vector4 stop , float t){
    return Vector4Add(Vector4Scale(start,std::max((1.f - t),0.f)),Vector4Scale(stop,std::min(1.f,t)));
}

void particle::initParticle(vec2 pos,vec2 vel,particleEmitterData* data){
    this->data = data;
    this->vel = vel;
    this->t.pos = pos;
    this->t.rot = 0;
    this->t.scale = data->start_endSize.x;
    lifeTime = 0;
    framesAlive = 0;
    alive = true;
}


void particle::update(f32 delta){
    framesAlive++;
    lifeTime = framesAlive * delta;
    t.pos = t.pos + vec2(vel.x*delta,vel.y*delta);
    vec2 a = vel*delta;
    t.rot = t.rot + data->rotSpeed * delta;
    t.scale = lerp(data->start_endSize.x,data->start_endSize.y,lifeTime/data->particle_lifetime);
    if(alive == true && lifeTime > data->particle_lifetime){
        alive = false;
    }
}
void particle::draw(){
    Vector4 startColor = ColorNormalize(data->startColor); 
    Vector4 endColor = ColorNormalize(data->endColor); 
    BeginBlendMode(data->blendMode);
        (data->tex).DrawFrame(data->texFrame,t,ColorFromNormalized(vec4lerp(startColor,endColor,lifeTime/data->particle_lifetime)));
    EndBlendMode();
}

bool particle::isAlive(){
    return alive;
}
