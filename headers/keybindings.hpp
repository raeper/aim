#pragma once

namespace aim {

        /*! Virtual keys.
         */
        enum class VKey : int {
#ifdef __linux__
                K_Esc = 1,
                K_1   = 2,
                K_2   = 3,
                K_3   = 4,
                K_4   = 5,
                K_5   = 6,
                K_6   = 7,
                K_7   = 8,
                K_8   = 9,
                K_9   = 10,
                K_0   = 11
#elif _WIN32
                K_Esc = 0x1B,
                K_1   = 0x31,
                K_2   = 0x32,
                K_3   = 0x33,
                K_4   = 0x34,
                K_5   = 0x35,
                K_6   = 0x36,
                K_7   = 0x37,
                K_8   = 0x38,
                K_9   = 0x39,
                K_0   = 0x30
#else
#error "Unknown platform!"
#endif
        };
}
