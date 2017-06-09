#include <thread>
#include <chrono>
#include "reactor.hpp"


void raep::EventsDispenser::operator()() {
        while (!this->finised) {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
}