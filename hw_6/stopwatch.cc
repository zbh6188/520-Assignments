#include "stopwatch.h"
#include <chrono>
#include <iostream>
using namespace std::chrono;

void Stopwatch::start() {
    if (isStop == false) {
        StartTime = high_resolution_clock::now();
    } else {
        StartTime = StopTime;
    }
    isStart = true;
    isStop = false;
}

void Stopwatch::stop() {
    if (isStop == false && isStart == true) {
        StopTime = high_resolution_clock::now();
        isStop = true;
    } 
}
double Stopwatch::get_milliseconds() {
    if (isStart == true && isStop == true) {
        duration<double, std::milli> time = (StopTime - StartTime);
        return time.count();
    } else if (isStart == true && isStop == false) {
        duration<double, std::milli> time = (high_resolution_clock::now() - StartTime);
        return time.count();
    } else {
        return 0;
    }
}

double Stopwatch::get_nanoseconds() {
    if (isStart == true && isStop == true) {
        duration<double, std::ratio<1,1000000>> time = (StopTime - StartTime);
        return time.count();
    } else if (isStart == true && isStop == false) {
        duration<double, std::ratio<1,1000000>> time = (high_resolution_clock::now() - StartTime);
        return time.count();
    } else {
        return 0;
    }
}

double Stopwatch::get_minutes() {
    if (isStart == true && isStop == true) {
        duration<double, std::ratio<60,1>> time = (StopTime - StartTime);
        return time.count();
    } else if (isStart == true && isStop == false) {
        duration<double, std::ratio<60,1>> time = (high_resolution_clock::now() - StartTime);
        return time.count();
    } else {
        return 0;
    }
}

double Stopwatch::get_seconds() {
    if (isStart == true && isStop == true) {
        duration<double, std::ratio<1,1>> time = (StopTime - StartTime);
        return time.count();
    } else if (isStart == true && isStop == false) {
        duration<double, std::ratio<1,1>> time = (high_resolution_clock::now() - StartTime);
        return time.count();
    } else {
        return 0;
    }
}

void Stopwatch::reset() {
    if (isStop == true) {
        isStart = false;
        isStop = false;
    }
}