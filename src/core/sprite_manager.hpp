#pragma once
#include "raylib/raylib.h"
#include <unordered_map>

#define DEBUG 

namespace Core{

class SpriteManager{
private:
    static std::unordered_map<const char *, Texture2D> loaded_textures;

public:
    static void loadTexture(const char* label,const char* path);
    static void loadTexture(const char* label,Image* image);
    static Texture2D* getTexture(const char* label);

    static bool searchTexture(const char* label);

    static void Destroy();
};

};
