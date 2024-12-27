#include <vector>

using namespace std;

class Solution {
public:
    long long minimumOperations(vector<int> &nums, vector<int> &target) {
        long long result = 0;
        int previous = 0;

        for (int i = 0; i < nums.size(); i++) {
            int difference = nums[i] - target[i];

            if (difference > 0) {
                if (previous >= 0) {
                    if (difference > previous)
                        result += difference - previous;
                } else {
                    result += difference;
                }
            } else {
                if (previous <= 0) {
                    if (difference < previous)
                        result += previous - difference;
                } else {
                    result -= difference;
                }
            }

            previous = difference;
        }

        return result;
    }
};