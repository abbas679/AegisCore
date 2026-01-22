#pragma once
#include "../core/EventBase.h"
#include <atomic>
#include <memory>
#include <vector>
#include <cassert>

namespace aegis {

// Lock-free single-producer, single-consumer queue for events
class EventQueue {
public:
    explicit EventQueue(size_t capacity)
        : capacity_(capacity), buffer_(new EventBase*[capacity]), head_(0), tail_(0) {}

    ~EventQueue() {
        while (head_ != tail_) {
            delete buffer_[head_ % capacity_];
            ++head_;
        }
        delete[] buffer_;
    }

    // Push event into the queue
    bool push(EventBase* evt) {
        size_t next_tail = (tail_.load(std::memory_order_relaxed) + 1) % capacity_;
        if (next_tail == head_.load(std::memory_order_acquire)) {
            // Queue full
            return false;
        }
        buffer_[tail_.load(std::memory_order_relaxed)] = evt;
        tail_.store(next_tail, std::memory_order_release);
        return true;
    }

    // Pop event from the queue
    EventBase* pop() {
        if (head_.load(std::memory_order_relaxed) == tail_.load(std::memory_order_acquire)) {
            // Queue empty
            return nullptr;
        }
        EventBase* evt = buffer_[head_.load(std::memory_order_relaxed)];
        head_.store((head_.load(std::memory_order_relaxed) + 1) % capacity_, std::memory_order_release);
        return evt;
    }

    bool empty() const {
        return head_.load() == tail_.load();
    }

private:
    const size_t capacity_;
    EventBase** buffer_;
    std::atomic<size_t> head_;
    std::atomic<size_t> tail_;
};

} // namespace aegis
