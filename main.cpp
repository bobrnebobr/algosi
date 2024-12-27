#include <vector>
#include <iostream>
#include "lab.cpp"

typedef long long ll;

using namespace std;

int main() {
    vector<int> nums = {3, 5, 1, 2};
    vector<int> target = {4, 6, 2, 4};
    auto solution = Solution();

    cout << solution.minimumOperations(nums, target);
}