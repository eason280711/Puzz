#include <windows.h>
#include <spdlog/logger.h>
#include <Core/Inherit.h>

extern "C" USER_API void SetLogger(std::shared_ptr<spdlog::logger> logger) {
    logger->info("DLL on");
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}