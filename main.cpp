#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

#include "sortings/tournamentSort.cpp"
#include "sortings/cartesianTreeSort.cpp"
#include "sortings/cycleSort.cpp"


bool is_sorted(vector<int> array) {
    for (int i=1; i<array.size(); i++) {
        if (array[i] < array[i - 1])
            return false;
    }
    return true;
}


std::chrono::duration<double> get_sorting_time(vector<int>& array, vector<int> (*func)(vector<int>&)) {
    auto start = std::chrono::high_resolution_clock::now();
    func(array);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

   return duration;
}

int main() {
    std::string filename = "../data/random_numbers.txt";

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("cannot open file");
    }

    std::vector<int> numbers;

    int num;
    int counter = 0;

    while (file >> num) {
        numbers.push_back(num);
        counter++;

        if (counter % 50000 == 0) {
            std::cout << counter << " " << get_sorting_time(numbers, cycleSort) << std::endl;
        }
    }
}