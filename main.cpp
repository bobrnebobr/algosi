#include <vector>
#include <iostream>
#include <string>
#include "lab.cpp"

typedef long long ll;

using namespace std;

int main() {
    vector<int> array = {0,1,2,3,4,8,9,11};

    Solution solution;
    cout << solution.canCross(array);
}