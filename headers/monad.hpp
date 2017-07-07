#pragma once
#include <utility>
#include <memory>
#include <optional>

namespace aim {

        template <typename T, template <typename...> typename Cont>
        struct is_valid {};

        template <typename T, template <typename...> typename Cont>
        struct make {};

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
                                return chain<subresult_type_t, Cont>{make<subresult_type_t, Cont>{}(std::move(func(*value)))};
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
                        return chain<TT, ContT>{make<decltype(func()), ContT>{}(func())};
                }
        };

}

namespace aim {
        template <typename T>
        struct is_valid<T, std::optional> {
                constexpr bool operator()(std::optional<T> const& value) {
                        return bool(value);
                }
        };

        template <typename T>
        struct make<T, std::optional> {
                auto operator()(T&& value) {
                        return std::optional{std::move(value)};
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
        struct make<T, std::unique_ptr> {
                auto operator()(T&& value) {
                        return std::make_unique<T>(std::move(value));
                }
        };
}
