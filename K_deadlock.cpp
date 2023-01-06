

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>

using namespace std;

mutex m1, m2, m3;

void f1() {
    m1.lock();
    this_thread::sleep_for(chrono::milliseconds(100));
    m2.lock();
    m2.unlock();
    m1.unlock();
}

void f2() {
    m2.lock();
    this_thread::sleep_for(chrono::milliseconds(100));
    m3.lock();
    m3.unlock();
    m2.unlock();
}

void f3() {
    m3.lock();
    this_thread::sleep_for(chrono::milliseconds(100));
    m1.lock();
    m1.unlock();
    m3.unlock();
}

int main() {
    thread t1(f1);
    thread t2(f2);
    thread t3(f3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

