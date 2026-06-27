#include <iostream>
#include <thread>
#include "../globals.h"
#include "./window/window.hpp"

void CheatThread();

int main() {
    std::thread(CheatThread).detach();

    Overlay overlay;
    overlay.SetupOverlay("Counter-Strike 2");

    while (overlay.shouldRun) {
        overlay.StartRender();
        overlay.Render();
        overlay.EndRender();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}