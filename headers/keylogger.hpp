#pragma once
#include <stdint.h>
#include "virtualkeys.hpp"

namespace raep {

        struct Keylogger {
                Keylogger()
                {}

                bool onPressed() const {
                        return false;
                }

        private:
        };
}