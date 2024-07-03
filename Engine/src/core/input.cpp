#include "input.hpp"
#include "raylib/raylib.h"

std::unordered_map<u8, std::vector<u16>> Core::InputHandler::KB_MOUSE_MAP;
std::unordered_map<u8, std::vector<u16>> Core::InputHandler::GAMEPAD_MAP;
std::unordered_map<u8, const char*> Core::InputHandler::EVENTS_NAME_MAP;

void Core::InputHandler::registerEvent(u8 event, const char* event_name, std::vector<u16> kb_inputs, std::vector<u16> mouse_inputs) {
    KB_MOUSE_MAP[event] = kb_inputs;
    GAMEPAD_MAP[event] = mouse_inputs;    
    EVENTS_NAME_MAP[event] = event_name;
}

bool Core::InputHandler::isEvent(u8 event) {
    bool pressed_in_keyboard = true;
    bool pressed_in_gamepad = true;

    for (u16 key : KB_MOUSE_MAP[event]) {
        // NOTE : Gowrish - key is a mouse event when < 7 otherwise
        // it is a keyboard event. Look at raylib.h
        bool pressed = (key > 7) ? IsKeyDown(key) : IsMouseButtonDown(key);
        pressed_in_keyboard &= pressed;
    }

    // TODO : Gowrish
    // for (u16 key : GAMEPAD_MAP[event]) {
    //     pressed_in_gamepad &= IsKeyPressed(key);
    // }

    // return pressed_in_gamepad || pressed_in_gamepad;
    return pressed_in_keyboard;
}
