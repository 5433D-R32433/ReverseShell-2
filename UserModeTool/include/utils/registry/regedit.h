#pragma once

#include <windows.h>

#include <array>
#include <string>


enum class Rootkeys
{
    _HKEY_CLASSES_ROOT                = 0,
    _HKEY_CURRENT_CONFIG,
    _HKEY_CURRENT_USER,
    _HKEY_LOCAL_MACHINE,
    _HKEY_USERS,
    number_of_items
};

/**
  * Use this class to manage a registry key.
  */
class Regkey
{
public:
    Regkey(Rootkeys root_key)
        : m_rootKey(root_keys[static_cast<std::size_t>(root_key)])
    {}
    
    // Copy is defaulted.
    Regkey(const Regkey& other)            = default;
    Regkey& operator=(const Regkey& other) = default;
    
    // Move is defaulted.
    Regkey(Regkey&& other)                 = default;
    Regkey& operator=(Regkey&& other)      = default;
    
    /**
      * Use this function to get an instance to a value\subkey
      * of the current key.
      * This creates the subkey if it doesn't exist.
      * Note that the extension of the directory is a value, not a subkey.
      * It becomes a subkey when you call operator[] from the new instance.
      * @param[in] extension - the last part of the directory.
      * @return an instance to a subdirectory of the current key.
      */
    Regkey operator[](std::string extension) const noexcept;
    
    /**
      * Use this function to set a value of the current key.
      * @param[in] value - a value to set.
      * @return value.
      */
    const std::string&  operator=(const std::string&  value) const noexcept;

    /**
      * Use this function to get a value of the current key.
      * This will raise if the value doesn't exist.
      * @return the requested value.
      */
    std::string get() const;
    
    /**
      * This function creates a key if it doesn't exist.
      * @return On success, true is returned.
      *         Otherwise, false is returned.
      */
    bool create() const noexcept;
    
    /**
      * This function removes a key if it exists.
      * Doesn't remove recursively.
      * @return On success, true is returned.
      *         Otherwise, false is returned.
      */
    bool remove() const noexcept;
    
private:

    /**
      * This array type translates a Rootkeys number to a matching
      * predefined HKEY.
      */
    using container = std::array<
                                HKEY,
                                static_cast<std::size_t>(Rootkeys::number_of_items)
                                >;

    /**
      * This array translates a Rootkeys number to a matching
      * predefined HKEY.
      */
    static const container root_keys;
    
    /**
      * 
      */
    HKEY m_rootKey;
    
    /**
      * The current subkey. This is a chain of all the extensions
      * passed to operator[] but the last.
      */
    std::string m_subKey;
    
    /**
      * The current subkey's requested value.
      * This is the last extension that was passed to operator[] .
      */
    std::string m_valueName;
      
    /**
      * operator[] uses this constructor to create an instance
      * to an extension.
      * The constructors creates the subkey if it doesn't exist.
      */
    Regkey(HKEY root_key, std::string subkey, std::string&& value_name)
        : m_rootKey(root_key),
          m_subKey(subkey),
          m_valueName(value_name)
    {
        create();
    }

    /**
      * This function hides a call to RegOpenKeyEx.
      * @param[in] result - a pointer to an HKEY to write the result to.
      * @return error code.
      */
    LONG openimpl  (PHKEY result) const noexcept;
    
    /**
      * This function hides a call to RegCreateKeyEx.
      * @param[in] result - a pointer to an HKEY to write the result to.
      * @return error code.
      */
    LONG createimpl(PHKEY result) const noexcept;
    
    /**
      * This function hides a call to RegSetValueEx.
      * @param[in] key - an HKEY that was previously opened.
      * @param[in] value - the value to be set.
      * @return error code.
      */
    LONG setimpl(HKEY key,
                 const std::string& value)
    const noexcept;
    
    /**
      * This function hides a call to RegQueryValueEx.
      * @param[in] key - an HKEY that was previously opened.
      * @param[in] buffer - a buffer to copy the value to.
      * @param[in, out] psize - when in, size of buffer.
      *                         when out, number of bytes copied to buffer.
      * @return error code.
      */
    LONG getimpl(HKEY key,
                 BYTE* buffer,
                 DWORD* psize)
    const noexcept;
    
    /**
      * This function template is used to call get & set implementations
      * to avoid code duplication.
      * @param[in] func - a function to call (getimpl, setimpl)
      * @param[in] args - arguments to send to func.
      * @return error code.
      */
    template<typename Func, typename... Args>
    LONG call(Func&& func, Args&&... args)
    const noexcept;    
};

