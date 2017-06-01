#include "reactor.hpp"

void raep::Reactor::exec() {
        while (!finised && !actors.empty()) {
                // TODO make actors execution async
                for (auto i = 0; i < actors.size(); ++i) {
                        for (auto& event : actors[i]->exec()) {
                                // TODO somehow pass arguments to handler?
                                auto handlerItr = handlers.find(i);
                                if (handlerItr != handlers.end())
                                        handlerItr->second();
                        }
                }
        }
}