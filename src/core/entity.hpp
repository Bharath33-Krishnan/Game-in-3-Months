#pragma once

#include "data_types.hpp"
#include <vector>


struct transform {
    vec3 pos;
    vec3 rot;
    vec3 scale;
};

namespace Core {

class EngineMaterial;

class AbstractEntity {
private:
    transform t;
public:
    virtual void init() = 0;
    virtual void update(f32 delta) = 0;
    virtual void addTexture(Texture2D& tex, i32 loc) = 0;
    virtual void draw() = 0;
    virtual Model* getModel(){return nullptr;}
    virtual ~AbstractEntity(){}

    inline transform& getTransform() { return t; }
};

}
