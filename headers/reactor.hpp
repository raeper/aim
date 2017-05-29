#include <functional>
#include <vector>
#include <deque>

#include "keylogger.hpp"

namespace raep {

        constexpr std::size_t EVENTS_SIZE_STEP = 1000u;

        using Event_t = int;
        using Callback_t = std::function<int(void)>;

        struct Event {
                Event_t eventType;
                // std::tuple<...> arguments;
        };

        struct Reactor {
                Reactor()
                {
                        //handlers.resize(EVENTS_SIZE_STEP);
                }

                void exec()
                {
                        /*
                        while (!finised || hasEvents()) {
                                for (auto event : events) {
                                        handlers[event]();
                                        events.pop_front();
                                }

                        }
                        */
                        while (!finised) {
                                if (keylogger.onPressed()) {
                                        finish();
                                }
                        }
                }

                bool hasEvents() const {
                        return !this->events.empty();
                }

                Event_t registerEvent(Callback_t callback) {
                        //if (handlers.size() + 1 > handlersCount) {
                        //        handlers.resize(handlers.size() + EVENTS_SIZE_STEP);
                        //}
                        handlers.push_back(callback);
                        return handlers.size() - 1;
                }

                void sendEvent(Event_t event) {
                        events.push_back(event);
                }

                void finish() {
                        finised = !finised;
                }

        private:
                bool finised = false;
                std::deque<Event_t> events;
                std::vector<Callback_t> handlers;
                std::size_t handlersCount;
                Keylogger keylogger;
        };
}