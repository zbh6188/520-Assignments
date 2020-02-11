#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <numeric>     // std::accumulate
#include "examples.h"
#include <tuple>
#include "db.h"

namespace {

  using namespace std;

  // class Imag {
  //     public: 
  //     Imag(double a, double b) : x(a), y(b) {}
  //     double x, y;
  // };

  // TEST(Vector,Vector) {

  //     vector<Imag> r;
  //     r.emplace(r.begin(),2.0,3.0);
  //     Imag h(1,2);
  //     r.push_back(h);

  //   vector<double> v;
  //   for (int i=0; i< 50; i++) {
  //     v.push_back(i);
  //   }
  //   v.pop_back();

  //   for (double &i : v)
  //     i *= i;
  //   for (double &i : v)        
  //     std::cout << i << " "; 

  //   std::cout << "\n";

  //   std::cout << v.capacity() << "\n";

  //   v.shrink_to_fit();

  //   std::cout << v.capacity() << "\n";
  //   v.push_back(1);
  //   std::cout << v.capacity() << "\n";     

  //   vector<int> w = { 1, 2, 3 };  // vector of three ints
  //   vector<double> x(10,3.14);    // vector of 10 3.14s
  //   vector<double> y = x;         // copy constructor with assignment operator       

  //   string s;
  //   string t = "hello";
  //   string u = t;

  //   t.pop_back();
  //   cout << t << ", "  << "\n";

  //   std::cout << u.capacity() << "\n";
  //   u.shrink_to_fit();    

  // }

  // TEST(VectorString,Common) {

  //     vector<double> v = { 1, 2, 3 };
  //     v.push_back(4);

  //     cout << v.empty() << v.size() << v[0] << (v==v) << (v!=v) << (v>v) << "\n";

  //     string s = "abc";
  //     s.push_back('d');

  //     cout << s << s.empty() << s.size() << s[0] << (s==s) << (s!=s) << (s>s) << "\n";

  //     vector<double> u;

  //     for ( double x : v ) {
  //         u.push_back(x);
  //     }

  //     string t;

  //     for ( char c : s ) {
  //         cout << c << "\n";
  //     }

  //     cout << t << "\n";    

  //       vector<string> V = { "i", "am", "on", "a", "bumpy", "flight" };
  //       for (string s : V ) {
  //           cout << s << "!\n";
  //       }      

  //       string q = "I know my ABC's and 123's.";


  //     for ( char &c : q ) {
  //         c = toupper(c);
  //     }

  //     for ( string::iterator i = q.begin(); i != q.end(); i++ ) {
  //         *i = tolower(*i);
  //     }      

  //     cout << q << "\n";

  //   auto i = v.begin();
  //   auto j = i + v.size() / 2;
  //   i < j; // true      

  //   q.insert(q.begin()+1, 'x');
  //   cout << q << "\n";
  //   q.erase(5,2);
  //   cout << q << "\n";


  // }

  // TEST(Find,Find) {
  //     vector<string> v = { "The", "quick", "brown", "fox" };
  //     string s = "this is a string";
  //     int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};      

  //     auto f1 = find(v.begin(), v.end(), "not quick");
  //     if ( f1 != v.end() ) {
  //       cout << *f1 << "\n";
  //     } else {
  //         cout << "not found \n";
  //     }

  //     auto f2 = find(s.begin(), s.end(), 'i');
  //     cout << *f2 << "\n"; 

  //     auto f3 = find(begin(a), end(a), 6);
  //     cout << *f3 << "\n";       

  // }

  // TEST(ALG,ALG) {
  //   vector<int> v = { 1, 2, 3, 4, 5 }, w = { 2,3,4,5,6,6,7,8 };
  //   cout << accumulate(v.begin(), v.end(), 0) << "\n"; // sum of the elements in v  
  //   cout << count(v.begin(), v.end(), 3) << "\n";
  //   cout << (equal(v.begin(), v.end(), w.begin()) ? "true" : "false") << "\n";
  //   sort(v.begin(), v.end());
  //   fill(v.begin(), v.end(), 1);
  //   fill_n(v.begin(), 3, 1);
  //   copy(v.begin(), v.end(), w.begin() + 3);
  //   replace(v.begin(), v.end(), 3,-1);
  // }

  // void add_to(vector<int> &v, int x) {
  //     transform(v.begin(), v.end(), v.begin(), [x](int y) { return x+y; });
  // }


  // TEST(LAMBDA,LAMBDA) {
  //  auto f = [](double x) { return x*x; };
  //  f(3);

  //   vector<int> v = { 1, 2, 3, 4, 5 };
  //   transform(
  //       v.begin(), 
  //       v.end(), 
  //       v.begin(),
  //       [](int x) { return x*x; }
  //   );

  //   for(auto x : v) {
  //       cout << x << "\n";
  //   }

  // }

  // TEST(Map,Map) {

  //   map<string,string> person;
  //   person["First"] = "Alan";
  //   person["Last"] = "Turing";
  //   person["Job"] = "Code breaker";

  //   map<string, vector<int>> sequence;
  //   sequence["fib"] = { 1, 1, 2, 3, 5, 8, 13 };
  //   sequence["ints"] = { 1, 2, 3, 4, 5, 6 };
  //   sequence ["squares"] = { 1, 4, 9, 16, 25, 36 };

  //   map<unsigned int, double> a;
  //   a[0] = 123;
  //   a[5] = 34;
  //   cout << "a[3] = " << a[3] << "\n";

  // }

  TEST(Examples, Sort) {
    vector<double> v = {71,45,-60};
    sort_by_magnitude(v);
    cout << "v[] = " << v[0] << v[1] << v[2] << "\n";
  }

  TEST(Examples, Prime) {
    vector<int> v = primes(30);
    for (int i = 0; i < v.size(); i++) {
      cout << v[i] << "\n";
    }
  }

  TEST(Examples, PrimeTwins) {
    vector<int> v = primes(30);
    vector<tuple<int,int>> tw = twins(v);
    for (const auto& i : tw) {
      cout << get<0>(i) << get<1>(i) << endl;

    }
  }

  TEST(DB,Basics) {

      DB db;

      db.insert("earth", 1, 1)            
        .insert("mars", 0.11, 1.524)
        .insert("moon", 0.012, 1)
        .insert("exoplanet one", 1, 1054.4)
        .insert("jupiter", 318, 5.2);

      ASSERT_EQ(NAME(db.find(0)), "earth");

      auto rows = db.where([](DB::Row row) { return  MASS(row) < 1; }); 

      ASSERT_EQ(rows.size(), 2);

      try {
          db.drop(2)                        
            .find(2);  
          FAIL();
      } catch ( runtime_error e ) {
          ASSERT_STREQ(e.what(), "Could not find an entry with the given key");
      }     

  }
  
  TEST(DB, Error) {
    DB db;

    db.insert("earth", 1, 1)            
      .insert("mars", 0.11, 1.524)
      .insert("moon", 0.012, 1)
      .insert("exoplanet one", 1, 1054.4);
      //.insert("earth", 318, 5.2);
  }

  TEST(DB, FindName) {
    DB db;
    db.insert("earth", 1, 1)            
      .insert("mars", 0.11, 1.524)
      .insert("moon", 0.012, 1)
      .insert("exoplanet one", 1, 1054.4);

    auto row = db.find_by_name("earth");
  
    cout << NAME(row) << "!\n";
  

    //auto notfind = db.find_by_name("apple");
  }

  TEST(DB, Random) {
    DB db;
    db.create_test_data(3);
    for (int i = 0; i < 3; i++) {
      auto test = db.find(i);
      cout << KEY(test) << NAME(test) << MASS(test) << DISTANCE(test) << "!\n";
    }
  }

  TEST(DB, Size) {
    DB db;
    int s = db.size();
    cout << s << "!\n";
    db.insert("earth", 1, 1)            
      .insert("mars", 0.11, 1.524)
      .insert("moon", 0.012, 1)
      .insert("exoplanet one", 1, 1054.4);
    int s2 = db.size();
    cout << s2 << "!\n";
    db.create_test_data(3);
    int s3 = db.size();
    cout << s3 << "!\n";
    db.drop(1);
    int s4 = db.size();
    cout << s4 << "!\n";
    DB dc;
    int s5 = dc.size();
    cout << s5 << "!\n";
  }

  TEST(DB, Add) {
    DB db;
    db.insert("earth", 1, 1)            
      .insert("mars", 0.11, 1.524)
      .insert("moon", 0.012, 1)
      .insert("exoplanet one", 1, 1054.4);

    double total_mass = db.accumulate([](DB::Row row) { return MASS(row); });
    double total_dis = db.accumulate([](DB::Row row) { return DISTANCE(row); });
    cout << total_mass << "!\n";
    cout << total_dis << "!\n";
  }

  TEST(DB, Average) {
    DB db;
    db.insert("earth", 1, 1)            
      .insert("mars", 2, 2.5)
      .insert("moon", 3, 1)
      .insert("exoplanet one", 2, 5.5);
    ASSERT_EQ(db.average_mass(), 2);
    ASSERT_EQ(db.average_distance(), 2.5);
  }

    
  

}

