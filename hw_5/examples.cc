#include <exception>
#include "examples.h"
#include <tuple>
#include <string>

using namespace std;

void sort_by_magnitude(vector<double> &x) {
    sort(x.begin(), x.end(), [](double i, double j) {return abs(i) < abs(j);});
}

vector<int> primes(int n) {
    vector<bool> isPrime(n+1, true);
    vector<int> result;
    for (int i = 2; i*i <= n; i++) {
        if (isPrime[i] == true) {
            for (int j = i*2; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    for (int k = 2; k <= n; k++) {
        if (isPrime[k]) {
            result.push_back(k);
        }
    }
    return result;
}

vector<tuple<int,int>> twins(vector<int> nums) {
    vector<tuple<int,int>> result;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i; j < nums.size(); j++) {
            if ((nums[j] - nums[i]) == 2) {
                auto p = make_tuple(nums[i], nums[j]);
                result.push_back(p);
            }
        }
    }
    return result;
}