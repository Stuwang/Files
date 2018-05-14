#include <iostream>
#include <thread>
#include <chrono>

#include "read_write_lock.h"

void test_rwlock_read() {
    using namespace qy;
    RWLock lock;
    std::thread t1{ [&]() {
        lock.RLock();
        std::cout << "read 1 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "read 1 end" << std::endl;
        lock.RUnLock();
     } };

    std::thread t2{ [&]() {
        lock.RLock();
        std::cout << "read 2 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "read 2 end" << std::endl;
        lock.RUnLock();
     } };

     t1.join();
     t2.join();
}


void test_rwlock_write() {
    using namespace qy;
    RWLock lock;
    std::thread t1{ [&]() {
        lock.WLock();
        std::cout << "write 1 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "write 1 end" << std::endl;
        lock.WUnLock();
     } };

    std::thread t2{ [&]() {
        lock.WLock();
        std::cout << "write 2 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "write 2 end" << std::endl;
        lock.WUnLock();
     } };

     t1.join();
     t2.join();
}

void test_rwlock_read_write() {
    using namespace qy;
    RWLock lock;
    std::thread t1{ [&]() {
        lock.RLock();
        std::cout << "read 1 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "read 1 end" << std::endl;
        lock.RUnLock();
     } };

    std::thread t3{ [&]() {
        lock.WLock();
        std::cout << "write 2 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "write 2 end" << std::endl;
        lock.WUnLock();
     } };

    std::thread t2{ [&]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        lock.RLock();
        std::cout << "read 2 start" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "read 3 end" << std::endl;
        lock.RUnLock();
     } };

     t1.join();
     t2.join();
     t3.join();
}

int main() {
    test_rwlock_read_write();
}