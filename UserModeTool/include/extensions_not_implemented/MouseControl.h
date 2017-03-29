#pragma once

#include <thread>
#include <Windows.h>
#include <WinUser.h>

class MouseControl
{
    #define ever ;;

    public:
        MouseControl();
        void Block();
        void Unblock();

    protected:

    private:
        void Block_Thread();
        std::thread blockThread;
};
