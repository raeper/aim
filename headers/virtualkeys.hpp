#include <unordered_map>
#include <stdint.h>

#include "crossplatformutils.hpp"

namespace raep {
        enum class VirtualKeys : uint8_t {
                1: LeftMouse
        };

        static const std::unordered_map<uint8_t, VirtualKeys> VirtualKeysBindings = {
                {VirtualKeys::LeftMouse, utils::Platform().Windows(1).value}
        };
}