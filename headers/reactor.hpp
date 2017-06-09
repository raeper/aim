#pragma once
#include <functional>
#include <vector>
#include <deque>
#include <memory>
#include <unordered_map>
#include <map>

#include "lockable.hpp"


namespace raep {

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
                /*! \brief Main aggregator procedure.
                 */
                virtual void exec() = 0;
        };

        struct EventsDispenser {
                EventsDispenser()
                {
                }

                ~EventsDispenser() {

                }

                /*! \brief Register event aggregator.
                 * \param type Event type group.
                 * \param value Event aggregator.
                 */
                void registerAggregator(const EventType type, std::unique_ptr<IEventsAggregator> value) {
                        //eventsAggregators[type] = std::move(value);
                }

                void finish() {
                        finised = !finised;
                }

                void operator()();

        private:
                bool finised = false;
                //std::map<EventType, Lockable<std::deque<EventArguments_t>>> eventsBus;
                std::map<EventType, Lockable<std::deque<int>>> eventsBus;
        };
}