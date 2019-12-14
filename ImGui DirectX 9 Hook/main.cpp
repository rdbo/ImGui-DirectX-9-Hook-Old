#include "includes.h"
#include "hook.h"

void* d3d9Device[119];
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
uintptr_t endSceneAddr;
EndScene oEndScene;

bool init = false;
long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!init)
	{
		InitImGui(pDevice);
		init = true;
	}

	//ImGui Main Loop

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	//Your code here
	ImGui::Begin("ImGui Window");
	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	//Original Function
	return oEndScene(pDevice);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	void* d3d9Device[119];
	if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
	{
		endSceneAddr = (uintptr_t)d3d9Device[42];
		oEndScene = (EndScene)TrampHook((char*)d3d9Device[42], (char*)hkEndScene, 7);
	}
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
	}

	return TRUE;
}