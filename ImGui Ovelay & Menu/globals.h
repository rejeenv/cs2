#pragma once
#include <vector>
#include <mutex>
#include "math.hpp" // TO JEST KLUCZOWE

struct PlayerESP {
    Vector2 head2D;
    Vector2 feet2D;
    bool isValid;
};

struct Config {
    bool bEsp = true;
};

extern std::vector<PlayerESP> g_espList;
extern std::mutex g_espMutex;
extern ViewMatrix g_ViewMatrix;
extern Config cfg;