#include <vector>
#include <iostream>
#include <string>
#include "lab.cpp"

typedef long long ll;

using namespace std;

int main() {
    vector<string> data = {"dog", "cat", "dad", "good"};
    vector<char> letters = {'a', 'a', 'c', 'd', 'd', 'd', 'g', 'o', 'o'};
    vector<int> scores = {1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0};

    Solution solution;
    cout << solution.maxScoreWords(data, letters, scores);
}