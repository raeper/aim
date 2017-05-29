
namespace raep {
namespace utils {
        struct Platform {
                constexpr Platform& Windows(uint8_t key) {
                        #ifdef _WIN32
                        value = key;
                        #endif
                        return *this;
                }

                constexpr Platform& Linux(uint8_t key) {
                        #ifdef __linux__
                        value = key;
                        #endif
                        return *this;
                }

                constexpr Platform& Default() {
                        value = 0;
                        return *this;
                }

        uint8_t value;
};
 
}
}