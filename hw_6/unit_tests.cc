#include "gtest/gtest.h"
#include "stopwatch.h"
#include "random_process.h"
#include "filter.h"
#include "integrator.h"
#include "derivative.h"
#include "elma/elma.h"
#include <thread>
#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

namespace {

    TEST(Stopwatch,Problem) {
      
      Stopwatch w; // should set the stopwatch to 0 seconds
      w.start(); 
      SLEEP;
      w.stop();    
      std::cout << w.get_seconds() << "\n"; // about 1.5
      SLEEP;
      std::cout << w.get_seconds() << "\n"; // still about 1.5
      w.start(); 
      SLEEP;
      w.stop();    
      std::cout << w.get_seconds() << "\n"; // about 3.0
      w.reset();
      std::cout << w.get_seconds() << "\n"; // 0.0
      
      // w.start();
      // SLEEP;
      // std::cout << w.get_seconds() << "\n"; // 1.5
      // w.start();
      // SLEEP;
      // w.start();
      // SLEEP;
      // w.stop();
      // std::cout << w.get_seconds() << "\n"; // 1.5
      w.start();
      SLEEP;
      w.reset();
      std::cout << w.get_seconds() << "\n"; // 1.5
      w.stop();
      w.reset();
      std::cout << w.get_seconds() << "\n"; // 0.0
    }

    TEST(RandomProcess, Problem) {
      elma::Manager m;

      RandomProcess r("random numbers");
      Filter f("filter");
      elma::Channel link("link");

      m.schedule(r, 1_ms)
      .schedule(f, 1_ms)
      .add_channel(link)
      .init()
      .run(100_ms);

      std::cout << f.value() << "\n";
    }

    TEST(Integrator, Problem) {
      elma::Manager m;
      RandomProcess r("random numbers");
      Integrator i("Integrator");
      elma::Channel link("link");

      m.schedule(r, 1_ms)
      .schedule(i, 1_ms)
      .add_channel(link)
      .init()
      .run(100_ms);

      std::cout << i.value() << "\n";
    }

    TEST(Derivative, Problem) {
      elma::Manager m;
      RandomProcess r("random numbers");
      Derivative d("derivative");
      elma::Channel link("link");

      m.schedule(r, 1_ms)
      .schedule(d, 1_ms)
      .add_channel(link)
      .init()
      .run(100_ms);

      std::cout << d.value() << "\n";
    }
}