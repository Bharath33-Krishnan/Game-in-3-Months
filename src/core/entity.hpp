#pragma once

#include "data_types.hpp"

struct transform {
    vec3 pos;
    vec3 rot;
    vec3 scale;
    vec3 forward;
    vec3 up;
};

namespace Core {

class AbstractEntity {
protected:
    transform t;
public:
    virtual void init() = 0;
    virtual void update(f32 delta) = 0;
    virtual void draw() = 0;
    virtual ~AbstractEntity(){};

    inline transform& getTransform() { return t; }
};

}
