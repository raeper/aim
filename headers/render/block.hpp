#pragma once
#include <string>

#include "colour.hpp"

namespace aim {

        /*! Text block.
         */
        template <typename StringT>
        struct Block {
                using string_t = StringT;

                Colour colour; /// Text colour
                Colour background; /// Text background colour
        };

        using StdBlock = Block<std::string>;
}
