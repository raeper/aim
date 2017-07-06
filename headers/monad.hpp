#include <utility>

namespace aim {

        template <typename T, template <typename> typename Cont>
        struct is_valid {};

        template <typename T, template <typename> typename Cont>
        struct chain;

        template <typename T, template <typename> typename Cont>
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
                                return chain<subresult_type_t, Cont>{Cont<subresult_type_t>{func(*value)}};
                        }
                        else {
                                return chain<subresult_type_t, Cont>{};
                        }
                }

                holder_t value;
        };

        template <typename TT, template <typename> typename ContT>
        struct chain : use<TT, ContT> {
                template <typename Func>
                constexpr auto otherwise(Func&& func) {
                        return chain<TT, ContT>{ContT<decltype(func())>{func()}};
                }
        };

}

// #include <optional>

// namespace aim {
//         template <typename T>
//         struct is_valid<T, std::optional> {
//                 constexpr bool operator()(std::optional<T> const& value) {
//                         return bool(value);
//                 }
//         };
// }

// #include <iostream>
// #include <memory>

// int main() {

//         {
//                 std::optional<int> a;

//                 aim::use(std::move(a)).with([](auto v) {
//                         std::cout << v << '\n';
//                         return 1;
//                 }).otherwise([](){
//                         std::cout << "it's none!\n";
//                         return 2;
//                 }).with([](auto v){
//                         std::cout <<  v << '\n';
//                         return 3;
//                 });
//         }
// }