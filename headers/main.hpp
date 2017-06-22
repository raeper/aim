#pragma once
#include <memory>
#include <thread>

#include "reactor.hpp"
#include "ioactor.hpp"

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