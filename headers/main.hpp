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
                        std::thread eventLoopThread(EventsDispenser{});
                        eventLoopThread.join();
                        return 0;
                }
        };
}