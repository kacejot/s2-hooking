#include "hooking.h"
#include "MinHook.h"

hooking::~hooking() {
    if (m_initialized)
        deinit();
}

MH_STATUS hooking::init() {
    MH_STATUS result = MH_OK;
    if (!m_initialized) {
        if (result = MH_Initialize(); MH_OK == result)
            m_initialized = true;
    }

    return result;
}

void hooking::deinit() {
    for (auto& [_, hi] : m_hooks) {
        if (hi.address)
            MH_DisableHook((LPVOID)hi.address);

         hi.deleter(hi.hook);
    }

    MH_Uninitialize();
    m_initialized = false;
}

MH_STATUS hooking::install(hook_info& hi) {
    MH_STATUS result = MH_OK;
    if (result = MH_CreateHook((LPVOID)hi.address, (LPVOID)hi.detour, (LPVOID*)&hi.original);  MH_OK != result)
        return result;

    if (result = MH_EnableHook((LPVOID)hi.address); MH_OK != result)
        return result;

    return result;
}
