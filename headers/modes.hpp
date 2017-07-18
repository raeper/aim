#pragma once

namespace aim {
        /*! Basic class for editor mode.
         */
        struct IMode {
                virtual ~IMode()
                {}
        };

        /*! Normal editor mode.
         * Use to enter editor commands. Without direct text editing.
         */
        struct NormalMode : IMode {
        };

        /*! Insert editor mode.
         * Use to direct insertation into text.
         */
        struct InsertMode : IMode {
        };

        /*! Selection editor mode.
         * Rows selection only.
         */
        struct SelectMode : IMode {
        };

        /*! Block selection editor mode.
         */
        struct BlockSelectMode : SelectMode {
        };
}
