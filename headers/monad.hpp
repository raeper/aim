#pragma once
#include <optional>

namespace aim {

        template <typename T>
        struct chain;

        template <typename T, typename Func>
        constexpr auto use(std::optional<T>&& value, Func&& func) -> chain<T>;

        template <typename T>
        struct chain {
                using value_type_t = T;
                using containter_type_t = std::optional<value_type_t>;
                containter_type_t value;

                chain()
                {}

                chain(containter_type_t&& value_)
                : value(std::move(value_))
                {}

                template <typename Func>
                constexpr auto otherwise(Func&& func) {
                        return chain<T>(std::move(func()));
                }

                template <typename Func>
                constexpr auto use(Func&& func) {
                        return aim::use(std::move(value), std::move(func));
                }
        };
        
        template <typename T, typename Func>
        constexpr auto use(std::optional<T>&& value, Func&& func) -> chain<T> {
                if (bool(value)) {
                        func(std::move(*value));
                        return chain<T>{};
                }
                else {
                        return chain<T>{std::move(value)};
                }
        }
}

// #include <iostream>

// int main() {
//         std::optional<int> a;

//         aim::use(std::move(a), [](auto v) {
//                 std::cout << v << '\n';
//                 return 1;
//         }).otherwise([] {
//                 std::cout << 2 << '\n';
//                 return 2;
//         }).use([](auto v) {
//                 std::cout << v << '\n';
//                 return 3;
//         });
// }