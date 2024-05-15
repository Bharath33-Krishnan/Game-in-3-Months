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


