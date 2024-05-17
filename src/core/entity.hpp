#pragma once

#include "data_types.hpp"


struct transform {
    vec2 pos;
    vec2 pivotOffset;
    f32 rot;
    f32 scale;
};

namespace Core {

class AbstractEntity {
protected:
    transform t;
    u32 layer = 0;
public:
    virtual void init() = 0;
    virtual void update(f32 delta) = 0;
    virtual void draw(u32 layer) = 0;
    virtual ~AbstractEntity(){}

    inline transform& getTransform() { return t; }
    inline u32 getLayer(){return layer;}
    inline void setLayer(u32 l){layer = l;}
};

}
