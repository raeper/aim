#include <iostream>

#include "reactor.hpp"

namespace raep {
        struct Application {
                Application()
                {}

                int run()
                {
                        auto event = reactor.registerEvent([](){
                                std::cout << "MESSAGE!" << std::endl;
                                return 0;
                        });

                        reactor.sendEvent(event);
                        reactor.exec();
                        return 0;
                }

        private:
                Reactor reactor;
                Keylogger keylogger;
        };
}