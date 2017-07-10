#include <boost/thread/thread.hpp>

#include "events_dispenser.hpp"


void aim::EventsDispenser::operator()(std::vector<IEventsProducer>&& producers, std::vector<IEvenetsSubscriber>&& subscribers) {
        boost::thread_group producers_threads;
        for (auto&& producer : producers) {
                producers_threads.create_thread([&eventsBus, &finised, obj=std::move(producer)]() {
                        obj->operator()(finised, eventsBus);
                });
        }

        while (!finised) {
                auto&& event = eventsBus.read();
                for (auto&& subscriber : subscribers) {
                        subscriber->operator()(finised, event);
                }
        }

        producers_threads.join_all();
}
