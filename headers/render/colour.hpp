#pragma once
#include <stdint.h>

namespace aim {
        /*! Colour element.
         */
        union Colour {
                struct {
                        uint8_t red;
                        uint8_t green;
                        uint8_t blue;
                        uint8_t alpha;
                };
                uint32_t value;
        };
}
