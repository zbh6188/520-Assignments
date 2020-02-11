#include <exception>
#include "db.h"
#include <random>

using namespace std;

DB::DB() : _next_key(0) {
    _size = 0;
}

DB &DB::insert(const string name, double mass, double distance) {
    for (int i = 0; i < _next_key; i++) {
        auto n = find(i);
        if (NAME(n) == name) {
            throw std::runtime_error("Name already exist");
        }
    }
    int key = _next_key++;
    _size++;
    _data[key] = make_tuple(name, mass, distance);
    return *this;

}

DB &DB::drop(int key) {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        _data.erase (e);
    }
    _size--;
    return *this;
}

DB::Row DB::to_row(int key, const DB::Value value) const {
    return make_tuple(key, get<0>(value), get<1>(value), get<2>(value));
}

DB::Row DB::find(int key) const {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        return to_row(key,e->second);
    } else {
        throw runtime_error("Could not find an entry with the given key");
    }

}

vector<DB::Row> DB::where(function<bool(const DB::Row)> f) const {

    vector<Row> rows;

    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        if ( f(row) == true ) {
            rows.push_back(row);
        }
    }

    return rows;

}

DB::Row DB::find_by_name(const string name) const {
    for (int i = 0; i < _next_key; i++) {
        auto n = find(i);
        if (NAME(n) == name) {
            return n;
        }
    }
    throw runtime_error("Could not find row by name");
}

DB &DB::create_test_data(int n) {
    static const char c[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
    int stringLength = 8;
    double massMax = 1000;
    double massMin = 0.01;
    double disMax = 10000000;
    double disMin = 0.1;
    
    for (int j = 0; j < n; j++) {
        string name;
        for (int i = 0; i < stringLength; i++) {
            name += c[rand() % 58 + 1];
        }
        // uniform_real_distribution<double> u(massMin, massMax);
        // default_random_engine re;
        
        double mass = (massMax - massMin) * ((double)rand()/(double)RAND_MAX) + massMin;
        double distance = (disMax - disMin) * ((double)rand()/(double)RAND_MAX) + disMin;
        insert(name, mass, distance);
    }
    
    return *this;
}

int DB::size() const{
    return _size;
}

double DB::accumulate(function<double(const Row)> f) const {
    double result;
    for (int i = 0; i < size(); i++) {
        auto row = find(i);
        result += f(row);
    }
    return result;
}

double DB::average_mass() const {
    double total_mass = accumulate([](DB::Row row) { return MASS(row); });
    double result = total_mass / size();
    return result;
}

double DB::average_distance() const {
    double total_dis = accumulate([](DB::Row row) { return DISTANCE(row); });
    double result = total_dis / size();
    return result;
}

