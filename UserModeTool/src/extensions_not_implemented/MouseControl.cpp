//#include "MouseControl.h"
//
//MouseControl::MouseControl()
//{
//    //blockThread = std::thread{&MouseControl::Block_Thread, this};
//}
//
//void MouseControl::Block()
//{
//    blockThread.detach();
//}
//
//void MouseControl::Unblock()
//{
//    WaitForSingleObject((void*)&blockThread, INFINITE);
//    CloseHandle((void*)&blockThread);
//}
//
//void MouseControl::Block_Thread()
//{
//    for(ever)
//    {
//        SetCursorPos(0, 0);
//    }
//}
