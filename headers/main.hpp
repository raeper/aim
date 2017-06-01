#pragma once
#include <memory>

#include "reactor.hpp"
#include "ioactor.hpp"

namespace raep {
        struct Application {
                Application()
                {}

                int run()
                {
                        auto inputActor = std::unique_ptr<IActor>(new InputActor());
                        const auto inputEventType = reactor.registerActor(std::move(inputActor));

                        reactor.registerHandler(inputEventType, [this]() {
                                reactor.finish();
                        });

                        reactor.exec();
                        return 0;
                }

        private:
                Reactor reactor;
        };
}