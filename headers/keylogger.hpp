#include <stdint.h>
#include <windows.h>

#include "virtualkeys.hpp"

namespace raep {

        struct Keylogger {
                Keylogger()
                {}

                bool onPressed() const {
                        //LPMSG lpMsg;
                        //HWND  hWnd;
                        //UINT  wMsgFilterMin;
                        //UINT  wMsgFilterMax;
                        //const auto ret = GetMessage(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
                        //return ret;
                        return bool(GetAsyncKeyState(160) & 1);
                }

        private:
        };
}