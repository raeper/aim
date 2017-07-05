#pragma once
#include <vector>
#include <utility>
#include <optional>
#include <tuple>
#include <iterator>
#include <initializer_list>
#include <algorithm>

namespace aim {

        /** Ordered hash map
         */
        template <typename KeyT, typename ValueT>
        struct hash_map {
                using key_t = KeyT;
                using value_t = ValueT;
                using hash_fn = std::hash<key_t>;
                using hash_t = decltype(hash_fn{}(std::declval<key_t>()));
                using pair_t = std::tuple<hash_t, value_t>;

                using data_t = std::vector<pair_t>;
                using iterator = typename data_t::iterator;
                using const_iterator = typename data_t::const_iterator;

                hash_map()
                {}

                hash_map(std::initializer_list<std::tuple<key_t, value_t>> other)
                {
                        for(auto&& item : other)
                                insert(std::get<0>(item), std::get<1>(item));
                }

                hash_map(const hash_map&) = default;
                hash_map(hash_map&&) = default;

                iterator begin() {
                        return std::begin(data_);
                }

                const_iterator begin() const {
                        return std::begin(data_);
                }

                iterator end() {
                        return std::end(data_);
                }

                const_iterator end() const {
                        return std::end(data_);
                }

                /** \brief Nonmutable iteration over map using function.
                 * \param func Function object takes type `pair_t` type as argument.
                 */
                template <typename Func>
                void iter(Func&& func) const {
                        for(auto&& node : data_)
                                func(node);
                }

                /** \brief Find existing element or return past-end element iterator.
                 */
                iterator find(const key_t& key) {
                        const auto hash_ = hash_fn{}(key);
                        auto res_ = _find(hash_);
                        return res_.found ? res_.itr : end();
                }

                /** |brief Find existing element or return past-end element iterator.
                 */
                const_iterator find(const key_t& key) const {
                        return find(key);
                }

                /** \brief Inserts new element to map.
                 * \param key Key to access.
                 * \param value New value.
                 * \return New element was created or reassigned to existing key.
                 */
                bool insert(const key_t& key, value_t&& value) {
                        const auto hash_ = hash_fn{}(key);
                        const auto& own = _find(hash_);
                        if (own.found) {
                                std::get<1>(*own.itr) = std::move(value);
                                return false;
                        }
                        else {
                                auto iter = own.itr;
                                data_.insert(iter, std::make_tuple(hash_, std::move(value)));
                                return true;
                        }
                }

                /** \brief Removes element by its key.
                 * \param key
                 * \return True if element was removed and false otherwise.
                 */
                bool remove(const key_t& key) {
                        const auto hash_ = hash_fn{}(key);
                        const auto& own = _find(hash_);
                        if (own.found) {
                                data_.erase(own.itr);
                                return true;
                        }
                        else {
                                return false;
                        }
                }

        private:

                struct search_result {
                        bool found; /// Element was found
                        iterator itr; /// Iterator to previous element
                };

                /** \brief Searches element by its key's hash.
                 * \param hash_ Key's hash.
                 */
                search_result _find(const hash_t hash_) {
                        auto itr = std::lower_bound(begin(), end(), std::make_tuple(hash_, value_t{}),
                        [](const auto& l, const auto& r) {
                                return std::get<0>(l) < std::get<0>(r);
                        });

                        if (itr != end() && std::get<0>(*itr) == hash_) {
                                return {true, itr};
                        }
                        return {false, itr};
                }

                data_t data_;
        };
}
