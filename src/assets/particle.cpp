#include "particle.hpp"




void particle::update(f32 delta){
    t.pos += vel*delta;
    t.rot += rotSpeed * delta;
    t.scale += scaleSpeed * delta;
}
void particle::draw(){
    BeginBlendMode(blendMode);
        sprite->DrawFrame(spriteFrame,t);
    EndBlendMode();
}
