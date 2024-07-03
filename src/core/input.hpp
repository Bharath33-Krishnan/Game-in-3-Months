#pragma once

#include "data_types.hpp"
#include <unordered_map>
#include <vector>

namespace Core {

class InputHandler {
public:
    static std::unordered_map<u8, std::vector<u16>> KB_MOUSE_MAP;
    static std::unordered_map<u8, std::vector<u16>> GAMEPAD_MAP;
    static std::unordered_map<u8, const char*> EVENTS_NAME_MAP;

    static bool isEvent(u8);
    static void registerEvent(u8, const char*, std::vector<u16>, std::vector<u16>);
};

}
