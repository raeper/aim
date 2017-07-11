#pragma once
/** Tools to create monadic chained expressions.
 * Example of usage:
 * \code{.cpp}
 *         aim::hash_map<int, int> map = {
 *                 {1, 1}, {2, 2}
 *         };
 *         const auto final_result = aim::use(std::move(map.find(1))).with([](auto value) {
 *                 std::cout << value << '\n';
 *                 return value * 2;
 *         }).otherwise([]{
 *                std::cout << "Map doesn't have key!\n";
 *                return 2;
 *         });
 *         // To access the final value:
 *         const auto value_container = final_result.value.get();
 *         // Resulting container always has value due to non-void otherwise block.
 * \code
 *
 */
#include <utility>
#include <memory>
#include <optional>

namespace aim {

        template <typename T, template <typename...> typename Cont>
        struct is_valid {};

        template <typename T, template <typename...> typename Cont>
        struct wrap {};

        template <typename T, template <typename...> typename Cont>
        struct unwrap {};

        template <typename T, template <typename...> typename Cont>
        struct chain;

        template <typename T, template <typename...> typename Cont>
        struct use {
                using value_type_t = T;
                using holder_t = Cont<value_type_t>;

                use()
                {}

                use(holder_t&& value)
                : value(std::move(value))
                {}

                template <typename Func>
                constexpr auto with(Func&& func){
                        using subresult_type_t = decltype(func(std::declval<value_type_t>()));
                        if (is_valid<T, Cont>{}(value)) {
                                return chain<subresult_type_t, Cont>{wrap<subresult_type_t, Cont>{}(std::move(func(*value)))};
                        }
                        else {
                                return chain<subresult_type_t, Cont>{};
                        }
                }

                holder_t value;
        };

        template <typename TT, template <typename...> typename ContT>
        struct chain : use<TT, ContT> {
                template <typename Func>
                constexpr auto otherwise(Func&& func) {
                        return chain<TT, ContT>{wrap<decltype(func()), ContT>{}(func())};
                }
        };

        template <typename T, template <typename...> typename Cont>
        auto lift(chain<T, Cont>&& value) {
                return unwrap<T, Cont>{}(std::move(value.value));
        }

        template <typename T, template <typename...> typename Cont>
        auto operator << (T& left, chain<T, Cont>&& right) {
                left = lift(std::move(right));
        }
}

namespace aim {
        template <typename T>
        struct is_valid<T, std::optional> {
                constexpr bool operator()(std::optional<T> const& value) {
                        return bool(value);
                }
        };

        template <typename T>
        struct wrap<T, std::optional> {
                constexpr auto operator()(T&& value) {
                        return std::optional{std::move(value)};
                }
        };

        template <typename T>
        struct unwrap<T, std::optional> {
                constexpr auto operator()(std::optional<T>&& value) {
                        return *value;
                }
        };
}

namespace aim {
        template <typename T>
        struct is_valid<T, std::unique_ptr> {
                constexpr bool operator()(std::unique_ptr<T> const& value) {
                        return bool(value);
                }
        };

        template <typename T>
        struct wrap<T, std::unique_ptr> {
                constexpr auto operator()(T&& value) {
                        return std::make_unique<T>(std::move(value));
                }
        };

        template <typename T>
        struct unwrap<T, std::unique_ptr> {
                constexpr auto operator()(std::unique_ptr<T>&& value) {
                        return *value;
                }
        };
}
