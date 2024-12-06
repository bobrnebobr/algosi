#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


template<typename T>
vector<T> patienceSort(const vector<T>& array) {
    vector<vector<T>> piles;

    for (const T &x: array) {
        auto it = lower_bound(piles.begin(), piles.end(), vector<T>{x},
                              [](const vector<T> &pile, const vector<T> &value) {
                                  return pile.back() < value[0];  // Сравниваем по вершине стопки
                              });

        if (it == piles.end()) {
            piles.push_back({x});
        } else {
            it->push_back(x);
        }
    }

    vector<T> sortedArr;
    while (!piles.empty()) {
        auto minIt = min_element(piles.begin(), piles.end(),
                                 [](const vector<T> &pile1, const vector<T> &pile2) {
                                     return pile1.back() < pile2.back();  // Сравниваем по вершине стопки
                                 });

        sortedArr.push_back(minIt->back());
        minIt->pop_back();

        if (minIt->empty()) {
            piles.erase(minIt);
        }
    }

    return sortedArr;
}