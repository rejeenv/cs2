// Globals.h
#pragma once
#include "include.h"
#include <mutex>

struct Settings {
    bool bAntiFlash = false;
    bool bTriggerbot = false;
    bool bBunnyhop = false;
    bool bEsp;

    float bTriggerbotShootDelay1 = 10;
};

extern Settings cfg;
extern std::vector<PlayerESP> g_espList;
extern std::mutex g_espMutex;