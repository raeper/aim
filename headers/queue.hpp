#pragma once
#include <queue>

namespace aim {
        template <typename T, template <typename...> class Subcontainer>
        struct Queue {
                using subcontainer_t = Subcontainer<T>;
                using value_type = T;

                value_type front() const {
                        return cnt.front();
                }

                value_type pop() {
                        auto ret = cnt.front();
                        cnt.pop();
                        return ret;
                }

                void push(value_type&& value) {
                        cnt.push(std::move(value));
                }

        private:
                subcontainer_t cnt;
        };

        template <typename T>
        using Queue_t = Queue<T, std::queue>;
}