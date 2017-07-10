#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <any>
#include <atomic>

#include "mutex_lock.hpp"
#include "queue.hpp"
#include "hashmap.hpp"


namespace aim {

        struct IEventsProducer {

                IEventsProducer()
                {}

                IEventsProducer(const IEventsProducer&) = default;
                IEventsProducer(IEventsProducer&&) = default;
                ~IEventsProducer() = default;

                virtual void exec() = 0;

                void operator()(std::atomic_bool& finised) {
                        while (!finised.load(std::memory_order::memory_order_relaxed)) {
                                this->exec();
                        }
                }
        };

        /*! \brief Events subsriber
         * \warning Can modify state of EventsDispenser: finished or not.
         */
        struct IEvenetsSubscriber {

        };

        struct EventsDispenser {

                EventsDispenser()
                {}

                EventsDispenser(EventsDispenser&&) = default;
                EventsDispenser(const EventsDispenser&) = delete;

                virtual ~EventsDispenser()
                {}

                void operator()(std::vector<IEventsProducer>&& producers, std::vector<IEvenetsSubscriber>&& subscribers);

        private:
                std::atomic_bool finised = false;

                MutexLock<Queue_t<std::any>> eventsBus;
        };
}
