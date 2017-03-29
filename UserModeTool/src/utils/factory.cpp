#include "utils/factory.h"

#include <windows.h>

#include "utils/registry/RegistryEditor.h"


bool
utils::factory::execute_on_startup()
{
    utils::registry::RegistryEditor editor;

    // get path of current file
    wchar_t exe_path[MAX_PATH];
    GetModuleFileNameW(NULL, exe_path, MAX_PATH);

    return ( editor.SetValue(HKEY_CURRENT_USER,
                    "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                    L"UserModeToolStarter",
                    L"\"" + std::wstring(exe_path) + L"\"") );
}
