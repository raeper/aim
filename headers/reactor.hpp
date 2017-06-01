#pragma once
#include <functional>
#include <vector>
#include <deque>
#include <memory>
#include <unordered_map>

namespace raep {

        constexpr std::size_t EVENTS_SIZE_STEP = 1000u;

        using Callback_t = std::function<void(void)>;

        using EventType_t = std::size_t;

        struct Event {
                EventType_t type;
        };

        /** \brief Events aggregator
         */
        struct IActor {
                virtual std::vector<Event> exec() = 0;
        };

        struct Reactor {
                Reactor()
                {
                }

                void exec();

                EventType_t registerActor(std::unique_ptr<IActor> actor) {
                        actors.emplace_back(std::move(actor));
                        return actors.size() - 1;
                }

                bool registerHandler(EventType_t eventType, Callback_t callback) {
                        if (eventType > (actors.size() - 1))
                                return false;
                        handlers[eventType] = callback;
                        return true;
                }

                void finish() {
                        finised = !finised;
                }

        private:
                bool finised = false;
                std::vector<std::unique_ptr<IActor>> actors;
                std::unordered_map<EventType_t, Callback_t> handlers;
        };
}