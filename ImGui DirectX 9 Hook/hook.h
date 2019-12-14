#pragma once
#include "includes.h"

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);
HWND GetProcessWindow();
bool GetD3D9Device(void** pTable, size_t Size);
bool Hook(char* src, char* dst, int len);
char* TrampHook(char* src, char* dst, unsigned int len);
void InitImGui(LPDIRECT3DDEVICE9 pDevice);