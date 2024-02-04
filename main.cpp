#include <iostream>
#include <priority_queue.hpp>
#include <timer.h>
#include <types.h>

int main() {
    yb::PriorityQueue<yb::TimerEvent, yb::TimerEvent::ComparatorAsc> queue;

    yb::TimerEvent data(false, 3_s,std::bind([](int i) {
        std::cout << "Function with int parameter: " << i << std::endl;
    }, 10));


    yb::TimerEvent data2(false, 5_s,std::bind([](float i) {
        std::cout << "Function with float  parameter: " << i << std::endl;
    }, 10));


    yb::TimerEvent data3(false, 1_s,std::bind([](double i) {
        std::cout << "Function with double  parameter: " << i << std::endl;
    }, 10));

    yb::TimerEvent data4(false, 0_s,std::bind([](char x) {
        std::cout << "Function with char  parameter: " << x << std::endl;
    }, 'a'));

    yb::TimerEvent data5(false, 0_s,std::bind([](char x, int z, double b) {
        std::cout << "Function with char  parameter: " << x << z << b << std::endl;
    }, 'a', 3, 5.2));

    queue.emplace(std::move(data));
    queue.emplace(std::move(data2));
    queue.emplace(std::move(data3));
    queue.emplace(std::move(data4));
    queue.emplace(std::move(data5));

    queue.emplace(yb::TimerEvent{false, 30_s,std::bind([](char x, int z, double b) {
        std::cout << "Function with prvalue";
    }, 'a', 3, 5.2)});

    /*
    yb::types::TimerEvent> ndata(std::move(*x), 3, true, 3_s, z);
    int *y = new int(32);
    yb::types::TimerEvent  ndata2(std::move(*y), 3, true, 3_s, z);

    queue.emplace(std::move(ndata));
    queue.emplace(std::move(ndata2));

    */

    queue[0].invokeCallBack();
    queue[1].invokeCallBack();
    queue[5].invokeCallBack();

    std::cout << "HELLO WORLD !";
    return 0;
}
