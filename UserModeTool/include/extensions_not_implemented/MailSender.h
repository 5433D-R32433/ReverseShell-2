#pragma once

#include <string>
#include <thread>
#include <windows.h>

using std::string;

class MailSender
{
    #define ever ;;

    public:
        MailSender();
        void Run();
        void SendMail();

    protected:

    private:
        string sender;
        string receiver;
        void SendMails();
        void CreateScript();
};
