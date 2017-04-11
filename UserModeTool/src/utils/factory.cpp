#include "utils/factory.h"

#include <windows.h>

#include "utils/registry/regedit.h"


bool
utils::factory::execute_on_startup()
{
    // get path of current file
    char exe_path[MAX_PATH];
    GetModuleFileNameA(NULL, exe_path, MAX_PATH);

    Regkey(Rootkeys::_HKEY_CURRENT_USER)["Software"]["Microsoft"]["Windows"]
    ["CurrentVersion"]["Run"]["UserModeToolStarter"] = "\"" + std::string(exe_path) + "\"";
}
