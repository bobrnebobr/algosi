#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <filesystem>

#include "sortings/tournamentSort.cpp"
#include "sortings/cartesianTreeSort.cpp"
#include "sortings/cycleSort.cpp"

namespace fs = std::filesystem;

std::chrono::duration<double> get_sorting_time(vector<int>& array, vector<int> (*func)(vector<int>&)) {
    auto start = std::chrono::high_resolution_clock::now();
    func(array);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    return duration;
}

int main() {
    std::string dir_path = "../data";

    for (const auto& entry : fs::directory_iterator(dir_path)) {
        // Получаем имя файла
        std::string filename = entry.path().filename().string();

        // Проверка на совпадение с шаблоном "sort_i"
        if (filename.substr(0, 15) == "random_numbers_" && filename.size() > 15) {
            int i = 0;
            try {
                i = std::stoi(filename.substr(15));
            } catch (const std::invalid_argument&) {
                continue;
            }

            if (i >= 0 && i <= 50) {
                std::ifstream file(entry.path());
                if (!file) {
                    std::cerr << "Unable to open file: " << entry.path() << std::endl;
                    continue;
                }

                std::vector<int> numbers;
                int number;

                while (file >> number) {
                    numbers.push_back(number);
                }

                file.close();

                std::cout << get_sorting_time(numbers, cycleSort) << std::endl;
            }
        }
    }
}