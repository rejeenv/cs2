#pragma once
#ifndef OFFSETS_H
#define OFFSETS_H
#include "wmemory.h"
#include <cstdint>

inline Wmemory cs2(L"cs2.exe");
//github.com/a2x/cs2-dumper/ - thx
namespace Offsets
{
	adr64 client = cs2.GetModuleBaseAddress(L"client.dll");

	const uintptr_t dwForceJump = 0x2065FA0;//bhop

	const uintptr_t dwLocalPlayerPawn = 0x2341698;

	const uintptr_t m_fFlags = 0x3F8;

	const uintptr_t dwViewAngles = 0x23568C8;

	const uintptr_t m_vecAbsVelocity = 0x3FC;

	const uintptr_t m_iIDEntIndex = 0x33FC;

	const uintptr_t dwEntityList = 0x24E76A0;

	const uint32_t m_hPlayerPawn = 0x90C;

	const uintptr_t m_iHealth = 0x34C;

	const uintptr_t m_iTeamNum = 0x3EB;

	const uintptr_t m_flFlashDuration = 0x1400;

	const uintptr_t m_vOldOrigin = 0x1390;

	const uintptr_t dwViewMatrix = 0x2346B30;

	const uintptr_t m_vOrigin = 0x8;

	const uintptr_t m_vecAbsOrigin = 0xC8;
}

#endif
