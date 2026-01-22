#pragma once
#include "../core/EventBase.h"
#include "../core/EventId.h"
#include "../queue/EventQueue.h"
#include <functional>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <memory>

namespace aegis {

class EventDispatcher {
public:
    using HandlerFunc = std::function<void(EventBase*)>;

    EventDispatcher() = default;

    // Register a handler for a specific event type
    template<typename EventT>
    void registerHandler(std::function<void(EventT*)> handler) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto wrapper = [handler](EventBase* e) {
            handler(static_cast<EventT*>(e));
        };
        handlers_[EventType<EventT>::id].push_back(wrapper);
    }

    // Dispatch events from a queue
    void dispatchQueue(EventQueue& queue) {
        while (EventBase* evt = queue.pop()) {
            dispatch(evt);
            delete evt; // automatically clean up after dispatch
        }
    }

    // Dispatch a single event
    void dispatch(EventBase* evt) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = handlers_.find(evt->type_id);
        if (it != handlers_.end()) {
            for (auto& h : it->second) {
                h(evt);
            }
        }
    }

private:
    std::unordered_map<EventId, std::vector<HandlerFunc>> handlers_;
    std::mutex mutex_;
};

} // namespace aegis
