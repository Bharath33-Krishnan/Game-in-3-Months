#pragma once

#include "entity.hpp"

namespace Core {

class Drawable :public AbstractEntity{
public:
    virtual void draw(u32 layer) override{
        if(this->layer == layer){
            drawGfx();
        }
    }

    virtual void drawGfx() = 0;
};

}
