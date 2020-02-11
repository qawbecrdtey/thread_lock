// Copyright (c) 2020 qawbecrdtey
// Please see LICENSE for license or visit https://github.com/qawbecrdtey/thread_lock/

#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

void add1(int i, long long &sum, std::mutex &mut) {
    long long adder = 0;
    for(int j = 0; j < i; j++) {
        adder += j;
    }
    mut.lock();
    sum += adder;
    mut.unlock();
}

void add2(int i, long long &sum, std::mutex &mut) {
    mut.lock();
    for(int j = 0; j < i; j++) {
        sum += j;
    }
    mut.unlock();
}

int main(int argc, char *argv[]) {
    int const size = std::stoi(argv[1]);
    std::cout << "Running size = " << size << std::endl;
    long long elapsed1 = 0, elapsed2 = 0;
    for(int tt = 0; tt < 10; tt++) {
        long long sum = 0;
        auto ta = new std::thread[size];
        std::mutex mut;

        // Case 1
        auto start = std::chrono::system_clock::now();
        for(int i = 0; i < size; i++) {
            ta[i] = std::thread(add1, i, std::ref(sum), std::ref(mut));
        }
        for(int i = 0; i < size; i++) ta[i].join();
        auto end = std::chrono::system_clock::now();

        printf("1 : %lld\n", sum);
        long long const e1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        elapsed1 += e1;
        std::cout << "Elapsed : " << e1 << std::endl;
        delete[] ta;

        sum = 0;
        ta = new std::thread[size];

        // Case 2
        start = std::chrono::system_clock::now();
        for(int i = 0; i < size; i++) {
            ta[i] = std::thread(add2, i, std::ref(sum), std::ref(mut));
        }
        for(int i = 0; i < size; i++) ta[i].join();
        end = std::chrono::system_clock::now();

        printf("2 : %lld\n", sum);
        long long const e2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        elapsed2 += e2;
        std::cout << "Elapsed : " << e2 << std::endl;
        delete[] ta;
    }
    std::cout << "Average for Case 1 : " << elapsed1 / 10 << std::endl;
    std::cout << "Average for Case 2 : " << elapsed2 / 10 << std::endl;
}