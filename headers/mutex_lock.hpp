#pragma once
#include <mutex>

namespace aim {

        template <typename T>
        struct MutexLock {
                using value_type = typename T::value_type;
                using container_type = T;

                MutexLock()
                {}

                MutexLock(const MutexLock&) = delete;

                value_type read() {
                        mutex.lock();
                        auto result = container.pop();
                        mutex.unlock();
                        return result;
                }

                void write(value_type&& value) {
                        mutex.lock();
                        container.push(std::move(value));
                        mutex.unlock();
                }

                value_type read_keep_lock() {
                        mutex.lock();
                        return container.pop();
                }

                void write_locked(value_type&& value) {
                        container.push(std::move(value));
                        mutex.unlock();
                }

        private:
                std::mutex mutex;
                container_type container;
        };
}