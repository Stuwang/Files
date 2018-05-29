#include <cassert>

#include "read_write_lock.h"

namespace qy {

RWLock::RWLock()
 : read_count_(0)
 , write_count_(0) {}

RWLock::~RWLock() {}

void RWLock::RLock() {
    std::unique_lock<std::mutex> lock(mutex_);
    while (0 != write_count_) {
        cond_.wait(lock);
    }
    read_count_++;
}

void RWLock::RUnLock() {
    std::unique_lock<std::mutex> lock(mutex_);
    read_count_--;
    assert(read_count_ >= 0);
    if (0 == read_count_ && 0 != write_count_) {
        cond_.notify_all();
    }
}

void RWLock::WLock() {
    std::unique_lock<std::mutex> lock(mutex_);
    while (0 != write_count_) {
        cond_.wait(lock);
    }
    write_count_++;
    while (0 != read_count_) {
        cond_.wait(lock);
    }
}

void RWLock::WUnLock() {
    std::unique_lock<std::mutex> lock(mutex_);
    write_count_--;
    cond_.notify_all();
}
}