#include "globals.h"
#include "offsets.h"
#include "memory.h"

extern Wmemory cs2;

void CheatThread() {
    while (true) {
        // Czytamy dane z gry
        g_ViewMatrix = cs2.ReadMemory<ViewMatrix>(Offsets::client + Offsets::dwViewMatrix);
        uintptr_t entityList = cs2.ReadMemory<uintptr_t>(Offsets::client + Offsets::dwEntityList);
        uintptr_t localPlayer = cs2.ReadMemory<uintptr_t>(Offsets::client + Offsets::dwLocalPlayerPawn);

        std::vector<PlayerESP> tempEspList;

        for (int i = 1; i < 64; i++) {
            uintptr_t listEntry = cs2.ReadMemory<uintptr_t>(entityList + (8 * (i & 0x7FFF) >> 9) + 16);
            if (!listEntry) continue;

            uintptr_t playerController = cs2.ReadMemory<uintptr_t>(listEntry + 120 * (i & 0x1FF));
            if (!playerController) continue;

            uint32_t pawnHandle = cs2.ReadMemory<uint32_t>(playerController + Offsets::m_hPlayerPawn);
            if (!pawnHandle) continue;

            uintptr_t listEntry2 = cs2.ReadMemory<uintptr_t>(entityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 16);
            if (!listEntry2) continue;

            uintptr_t playerPawn = cs2.ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
            if (!playerPawn || playerPawn == localPlayer) continue;

            Vector3 feetPos = cs2.ReadMemory<Vector3>(playerPawn + Offsets::m_vOrigin);
            Vector3 headPos = { feetPos.x, feetPos.y, feetPos.z + 75.0f };

            Vector2 feet2D, head2D;
            if (WorldToScreen(feetPos, feet2D, g_ViewMatrix, 1920.0f, 1080.0f) &&
                WorldToScreen(headPos, head2D, g_ViewMatrix, 1920.0f, 1080.0f)) {

                tempEspList.push_back({ head2D, feet2D, true });
            }
        }

        {
            std::lock_guard<std::mutex> lock(g_espMutex);
            g_espList = tempEspList;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}