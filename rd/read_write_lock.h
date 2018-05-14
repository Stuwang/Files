#include <mutex>
#include <condition_variable>
#include <cstdint>

namespace qy {

class RWLock {
public:
    RWLock();
    ~RWLock();
    void RLock();
    void RUnLock();

    void WLock();
    void WUnLock();

    RWLock(const RWLock&) = delete;
    RWLock& operator=(const RWLock&) = delete;

private:
    std::mutex mutex_;
    std::condition_variable cond_;
    uint8_t read_count_;
    uint8_t write_count_;
};   // end
}