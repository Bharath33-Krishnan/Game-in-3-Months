#pragma once

#include "data_types.hpp"
#include <vector>


struct transform {
    vec2 pos;
    f32 rot;
    f32 scale;
};

namespace Core {

class EngineMaterial;

class AbstractEntity {
protected:
    transform t;
public:
    virtual void init() = 0;
    virtual void update(f32 delta) = 0;
    virtual void draw() = 0;
    virtual Model* getModel(){return nullptr;}
    virtual ~AbstractEntity(){}

    inline transform& getTransform() { return t; }
};

}
