#pragma once
#include <mutex>

namespace aim {

        template <typename T>
        struct Lockable {
                using value_type = typename T::value_type;
                using container_type = T;

                Lockable()
                {}

                Lockable(const Lockable&) = delete;

                /*! \brief Blockable reading.
                 */
                value_type read() {
                        mutex.lock();
                        const auto&& result = container.front();
                        container.pop();
                        mutex.unlock();
                        return result;
                }

                /*! \brief Blockable writting.
                 */
                void write(value_type&& value) {
                        mutex.lock();
                        container.push(std::move(value));
                        mutex.unlock();
                }

        private:
                std::mutex mutex;
                container_type container;
        };

}