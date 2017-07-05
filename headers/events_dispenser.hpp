#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <any>

#include "mutex_lock.hpp"
#include "queue.hpp"
#include "hashmap.hpp"


namespace aim {

        constexpr std::size_t EVENTS_SIZE_STEP = 1000u;

        using EventArguments_t = std::function<void(void)>;

        enum class EventType : std::size_t {
                InputEvent,
                ControlEvent
        };

        /*! \brief Basic class for events aggregator.
         * Can collect only one type of events. Lives in separate thread.
         */
        struct IEventsAggregator {

                IEventsAggregator()
                {}

                IEventsAggregator(const IEventsAggregator&) = default;
                IEventsAggregator(IEventsAggregator&&) = default;
                ~IEventsAggregator() = default;

                /*! \brief Main aggregator procedure.
                 */
                virtual void exec() = 0;
        };

        struct EventsDispenser {
                EventsDispenser()
                {}

                EventsDispenser(EventsDispenser&&) = default;
                EventsDispenser(const EventsDispenser&) = delete;

                ~EventsDispenser()
                {}

                /*! \brief Register event aggregator.
                 * \param type Event type group.
                 * \param value Event aggregator.
                 */
                void registerAggregator(const EventType type, std::unique_ptr<IEventsAggregator> value) {
                        eventsAggregators.insert(type, std::move(value));
                }

                void finish() {
                        finised = !finised;
                }

                void operator()();

        private:
                bool finised = false;

                hash_map<EventType, std::unique_ptr<IEventsAggregator>> eventsAggregators;
                hash_map<EventType, MutexLock<Queue_t<std::any>>> eventsBus;
                hash_map<EventType, std::vector<int>> subscribers;
        };
}