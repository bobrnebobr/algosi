#include <vector>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>

#include "sortings/patienceSort.cpp"

using namespace std;
using namespace chrono;

int MOD=1e7;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, MOD);

    vector<int> array(1000000);

    for (int i=0; i<1000000; i++)
        array[i] = dis(gen);

    for (int n=1000; n<=1e6; n+=1000) {
        auto start = high_resolution_clock::now();

        vector<int> arr(array.begin(), array.begin() + n);

        patienceSort(arr);

        auto end = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(end- start);

        cout << n << " " << duration.count() << " milliseconds" << endl;
    }

    return 0;
}