#pragma once
#include <mutex>

namespace aim {

        template <typename MutexType, typename T>
        struct IMutexLock {
                using mutex_t = MutexType;
                using value_type = typename T::value_type;
                using container_type = T;

                IMutexLock()
                {}

                IMutexLock(const IMutexLock&) = delete;

                value_type read() {
                        std::lock_guard<mutex_t> lock(mutex);
                        auto result = container.pop();
                        return result;
                }

                void write(value_type&& value) {
                        std::lock_guard<mutex_t> lock(mutex);
                        container.push(std::move(value));
                }

        private:
                mutex_t mutex;
                container_type container;
        };

        template <typename T>
        using MutexLock = IMutexLock<std::mutex, T>;
}