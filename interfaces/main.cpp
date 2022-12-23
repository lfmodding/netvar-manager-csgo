#include <Windows.h>
#include <iostream>

#include "interfaces.h"

template <typename T>
T* GetInterface(const char* name, const char* library)
{
	const auto handle = GetModuleHandle(library);

	if (!handle)
		return nullptr;

	const auto functionAddress = GetProcAddress(handle, "CreateInterface");

	if (!functionAddress)
		return nullptr;

	using Fn = T * (*)(const char*, int*);

	const auto CreateInterface = reinterpret_cast<Fn>(functionAddress);

	return CreateInterface(name, nullptr);
}





void HackThread(HMODULE instance)
{
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);

	client = GetInterface<IClient>("VClient018", "client.dll");
	std::cout << "client interface: " << client << std::endl;
	entityList = GetInterface<IClientEntityList>("VClientEntityList003", "client.dll");
	std::cout << "enititylist interface: " << entityList << std::endl;

	SetupNetvars();

	while (!GetAsyncKeyState(VK_END))
	{
		
	}

	if (file)
		fclose(file);

	FreeConsole();
	FreeLibraryAndExitThread(instance, 0);
}

BOOL WINAPI DllMain(HMODULE instance, DWORD reason, LPVOID reserved)
{

	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);

		const auto thread = CreateThread(
							nullptr,
							0,
							reinterpret_cast<LPTHREAD_START_ROUTINE>(HackThread),
							instance,
							0,
							nullptr
							);

		if (thread)
		{
			CloseHandle(thread);
		}
	}

	return TRUE;
}