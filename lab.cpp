#include <map>
#include <unordered_set>
#include <unordered_map>


class Solution {
public:
    bool canCross(std::vector<int>& stones) {
        std::unordered_map<int, std::unordered_set<int>> dp;

        dp[1] = {1};

        for (auto stone: stones) {
            if (dp[stone].empty())
                continue;

            for (auto k: dp[stone]) {
                dp[stone + k - 1].insert(k - 1);
                dp[stone + k].insert(k);
                dp[stone + k + 1].insert(k + 1);
            }
        }

        if (dp[stones[stones.size() - 1]].empty())
            return false;
        else
            return true;
    }
};