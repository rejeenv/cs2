#include "../include.h"
#include "../globals.h"
#include "../math.hpp"
#include "window/window.hpp"

#include <thread>

void EmulateLeftClick()
{
	INPUT input[2] = {};

	input[0].type = INPUT_MOUSE;
	input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	input[1].type = INPUT_MOUSE;
	input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	SendInput(2, input, sizeof(INPUT));
}


// cheat
void CheatThread() {
    while (true) {

        g_ViewMatrix = cs2.ReadMemory<ViewMatrix>(Offsets::client + Offsets::dwViewMatrix);
        uintptr_t localPlayer = cs2.ReadMemory<uintptr_t>(Offsets::client + Offsets::dwLocalPlayerPawn);
        uintptr_t entityList = cs2.ReadMemory<uintptr_t>(Offsets::client + Offsets::dwEntityList);

        if (localPlayer != 0) {
            int crosshairID = cs2.ReadMemory<int>(localPlayer + Offsets::m_iIDEntIndex);
            int flags = cs2.ReadMemory<int>(localPlayer + Offsets::m_fFlags);
            Vector3 velocity = cs2.ReadMemory<Vector3>(localPlayer + Offsets::m_vecAbsVelocity);

            if (cfg.bAntiFlash) cs2.WriteMemory<float>(localPlayer + Offsets::m_flFlashDuration, 0.0f);
            if (cfg.bTriggerbot && crosshairID > 0) {
                Sleep(cfg.bTriggerbotShootDelay1);
                EmulateLeftClick();
            }
            if (cfg.bBunnyhop && (GetAsyncKeyState(VK_SPACE) & 0x8000)) {
                cs2.WriteMemory<int>(Offsets::client + Offsets::dwForceJump, (flags & (1 << 0)) ? 65537 : 256);
            }
        }

        std::vector<PlayerESP> tempList;
        for (int i = 1; i < 64; i++) {
            uintptr_t listEntry = cs2.ReadMemory<uintptr_t>(
                entityList + 0x8 * ((i & 0x7FFF) >> 9) + 0x10
            );
            if (!listEntry) continue;


            uintptr_t playerController = cs2.ReadMemory<uintptr_t>(
                listEntry + 0x78 * (i & 0x1FF)
            );

            if (!playerController) continue;
            if (playerController > 0x7FFFFFFFFFFF) continue;

            uint32_t pawnHandle = cs2.ReadMemory<uint32_t>(
                playerController + Offsets::m_hPlayerPawn
            );


            if (pawnHandle == 0 || pawnHandle == 0xFFFFFFFF) continue;

            uintptr_t listEntry2 = cs2.ReadMemory<uintptr_t>(
                entityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10
            );
            if (!listEntry2) continue;

            uintptr_t playerPawn = cs2.ReadMemory<uintptr_t>(
                listEntry2 + 0x78 * (pawnHandle & 0x1FF)
            );
            if (!playerPawn) continue;

            printf("success: player %d! Pawn: %llx\n", i, playerPawn);

            Vector3 origin = cs2.ReadMemory<Vector3>(playerPawn + Offsets::m_vecAbsOrigin);
            Vector3 head = origin;
            head.z += 75.0f;

            Vector2 feet2D, head2D;
            bool feetOk = WorldToScreen(origin, feet2D);
            bool headOk = WorldToScreen(head, head2D);

            printf("W2S: feet=%d (%.1f,%.1f) head=%d (%.1f,%.1f) | origin=(%.1f,%.1f,%.1f)\n",
                feetOk, feet2D.x, feet2D.y,
                headOk, head2D.x, head2D.y,
                origin.x, origin.y, origin.z);

            PlayerESP esp;
            esp.isValid = false;

            printf("=== pawnhandle for cotroller %llx ===\n", playerController);
            for (int offset = 0; offset < 0x800; offset += 4) {
                uint32_t val = cs2.ReadMemory<uint32_t>(playerController + offset);
                if ((val & 0x7FFF) > 0 && (val & 0x7FFF) < 64 && val != 0xFFFFFFFF) {
                    printf("potential handle @ offset 0x%x = 0x%x (indeks=%d)\n",
                        offset, val, val & 0x1FF);
                }
            }


            if (WorldToScreen(origin, feet2D) && WorldToScreen(head, head2D)) {
                esp.isValid = true;
                esp.feet2D = feet2D;
                esp.head2D = head2D;
                tempList.push_back(esp);
            }
        }
        {
            std::lock_guard<std::mutex> lock(g_espMutex);
            g_espList = tempList;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main()
{
	Overlay overlay;
	// thread your cheat here 
	std::thread(CheatThread).detach();

	// hide console window since we're making our own window, or use WinMain() instead.
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	printf("[>>] Hit insert to show the menu in this overlay!\n");
	overlay.SetupOverlay("totally not a cheat");

	while (overlay.shouldRun)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		overlay.StartRender();
        overlay.Render();

		if (overlay.RenderMenu) {

		}
		else
		ImGui::GetBackgroundDrawList()->AddText({ 1920, 540 }, ImColor(0.0f, 1.0f, 0.0f), "Overlay Rendering!");
		

		// if you want to render here, you could move the imgui includes to your .hpp file instead of the .cpp file!
		overlay.EndRender();
	}

}