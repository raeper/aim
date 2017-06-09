#pragma once
#include "reactor.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

namespace raep {
        struct InputEventAggregator : IEventsAggregator {
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