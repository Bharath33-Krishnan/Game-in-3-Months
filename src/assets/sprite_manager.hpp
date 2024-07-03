#pragma once

#include "raylib/raylib.h"
#include <cstdint>
#include <data_types.hpp>
#include <unordered_map>
#include "../core/entity.hpp"

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


class SpriteSheet{
private:
    vec2 initial_padding;
    vec2 stride;
    bool loop;
    int curr_frame;
    int max_frame;
    int frame_speed;
    int frame_counter = 0;
    Texture2D* tex;

    SpriteSheet(const char* label,vec2 initial_padding,int max_frame,int num_row,int num_rows,bool loop);
public:
    SpriteSheet();
    static SpriteSheet CreateSpriteSheet(const char* label,vec2 initial_padding,int max_frame,int num_row,int num_rows,bool loop = false);
    void AnimateFrame(transform& transform,const Color tint = WHITE);
    inline void ChangeFPS(int fps){
        frame_speed = fps;
    }
    inline int getFPS(){
        return frame_speed;
    }
    void DrawFrame(int frame,transform& transform,const Color tint = WHITE);
};
