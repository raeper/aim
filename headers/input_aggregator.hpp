#pragma once
#include "events_dispenser.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

namespace aim {
        struct InputEventProducer : IEventsProducer {
                virtual void exec() override {
#ifdef _WIN32
                        LPMSG lpMsg;
                        HWND  hWnd;
                        UINT  wMsgFilterMin;
                        UINT  wMsgFilterMax;
                        const auto ret = GetMessage(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
#endif
                        //return {{0u}};
                }
        };
}