#ifndef _STOPWATCH_H
#define _STOPWATCH_H
#include <chrono>
using namespace std::chrono;

class Stopwatch {
    public:
    void start();              // starts the timer
    void stop();               // stops the timer
    void reset();              // sets stopwatch to zero
    double get_minutes();      // number of minutes counted, as a double
    double get_seconds();      // number of seconds counted, as a double
    double get_milliseconds(); // number of milliseconds counted, as a double
    double get_nanoseconds();  // number of nanoseconds counted, as a double

    private:
    high_resolution_clock::time_point StartTime;
    high_resolution_clock::time_point StopTime;
    bool isStart = false;
    bool isStop = false;
};

#endif