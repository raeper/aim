#pragma once
#include <memory>
#include <thread>

#include "events_dispenser.hpp"
#include "input_aggregator.hpp"

namespace aim {
        struct Application {
                Application()
                {}

                int run()
                {
                        std::thread eventLoopThread(dispenser);
                        eventLoopThread.join();
                        return 0;
                }

        private:
                EventsDispenser dispenser;
        };
}