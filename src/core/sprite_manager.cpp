#include "sprite_manager.hpp"
#include "raylib/raylib.h"

#define LITERAL_TO_STRING(string) #string

std::unordered_map<const char * , Texture2D> Core::SpriteManager::loaded_textures;

#ifdef DEBUG
#include <cstring>
#include <string>
#include <cstdint>
#define d 256
// NOTE : BHARATH -> cursed gfg code for searching, only useful for debugging
bool search(const char* pat,const char* txt, int q) 
{ 
    int M = strlen(pat); 
    int N = strlen(txt); 
    int i, j; 
    int p = 0; // hash value for pattern 
    int t = 0; // hash value for txt 
    int h = 1; 
  
    // The value of h would be "pow(d, M-1)%q" 
    for (i = 0; i < M - 1; i++) 
        h = (h * d) % q; 
  
    // Calculate the hash value of pattern and first 
    // window of text 
    for (i = 0; i < M; i++) { 
        p = (d * p + pat[i]) % q; 
        t = (d * t + txt[i]) % q; 
    } 
  
    // Slide the pattern over text one by one 
    for (i = 0; i <= N - M; i++) { 
  
        // Check the hash values of current window of text 
        // and pattern. If the hash values match then only 
        // check for characters one by one 
        if (p == t) { 
            /* Check for characters one by one */
            for (j = 0; j < M; j++) { 
                if (txt[i + j] != pat[j]) { 
                    break; 
                } 
            } 
  
            // if p == t and pat[0...M-1] = txt[i, i+1, 
            // ...i+M-1] 
  
            if (j == M) 
                return true;
        } 
  
        // Calculate hash value for next window of text: 
        // Remove leading digit, add trailing digit 
        if (i < N - M) { 
            t = (d * (t - txt[i] * h) + txt[i + M]) % q; 
  
            // We might get negative value of t, converting 
            // it to positive 
            if (t < 0) 
                t = (t + q); 
        } 
    } 
    return false;
} 



bool Core::SpriteManager::searchTexture(const char *label){
    std::string searchMatches = "";
    for(auto pair:loaded_textures){
        if(search(label,pair.first,INT32_MAX))
        {
            if(strlen(label) == strlen(pair.first))
                return true;
            if(searchMatches.length() == 0)
                searchMatches+=TextFormat("%s",pair.first);
            else
                searchMatches+=TextFormat(", %s",pair.first);
        }
            
    }
    
    TraceLog(LOG_INFO, "WRONG LABEL: Label not found, Did you mean : %s", searchMatches.c_str());
    return false;
}
#endif 
#ifndef DEBUG

bool Core::SpriteManager::searchTexture(const char *label){
    return true;
}

#endif 

void Core::SpriteManager::loadTexture(const char *label, const char *path){
    loaded_textures[label] = LoadTexture(path);
}

void Core::SpriteManager::loadTexture(const char *label, Image* image){
    loaded_textures[label] = LoadTextureFromImage(*image);
}

Texture2D* Core::SpriteManager::getTexture(const char *label){
    if(searchTexture(label))
        return &loaded_textures[label];
    else
        return nullptr;
}



void Core::SpriteManager::Destroy(){
    for(auto pair:loaded_textures){
        UnloadTexture(pair.second);
    }
}

// ************** SPRITE SHEET CLASS ***************

SpriteSheet::SpriteSheet(){
    tex = nullptr;
}

SpriteSheet::SpriteSheet(const char* label,vec2 initial_padding,int max_frame,int num_row,int num_rows,bool loop){
        tex = Core::SpriteManager::getTexture(label);
        if (tex == nullptr || num_row >= num_rows){
            TraceLog(LOG_ERROR, 
                     "Texture Could Not Be Found num_row: %d num_rows: %d", 
                     num_row, 
                     num_rows);
        }
        curr_frame = 0;
        frame_counter = 0;
        this->loop = loop;
        this->stride = {(float)tex->width / max_frame ,(float)tex->height/num_rows};
        this->max_frame = max_frame;
        this->initial_padding = initial_padding;
        this->initial_padding.y += num_row * this->stride.y;
        this->frame_speed =  max_frame;
}


SpriteSheet SpriteSheet::CreateSpriteSheet(const char* label,vec2 initial_padding,int max_frame,int num_row,int num_rows,bool loop)
{
    return SpriteSheet(label,initial_padding,max_frame,num_row,num_rows,loop);
}

void SpriteSheet::AnimateFrame(transform& transform){
    if(tex == nullptr)
        return;

    float fps = GetFPS();
    frame_counter++;

    if(frame_counter >= fps/frame_speed){
        frame_counter = 0;
        curr_frame = (curr_frame + 1);
        if(loop)
            curr_frame %= max_frame;
        else if(curr_frame >= max_frame)
            curr_frame = max_frame - 1;
    }

    DrawFrame(curr_frame , transform);

}


void SpriteSheet::DrawFrame(int frame,transform& transform){
    if(tex == nullptr)
        return;
    if(frame >= max_frame){
        frame = max_frame - 1;
    }
    Rectangle src = {initial_padding.x + stride.x * frame,initial_padding.y,stride.x,stride.y};
    Rectangle dest = {transform.pos.x, transform.pos.y , stride.x * transform.scale , stride.y * transform.scale};

    //NOTE : BHARATH -> For Custom Offset you need to include a offset parameter and modify the third parameter here
    DrawTexturePro(*tex,src, dest, {stride.x * transform.scale/2,stride.y * transform.scale/2}, transform.rot, WHITE);
}
