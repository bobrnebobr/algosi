#include <vector>
#include <iostream>
#include <map>
#include <string>

typedef long long ll;

using namespace std;

string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

class Solution {
public:
    int maxScoreWords(vector<string> &words, vector<char> &letters, vector<int> &score) {
        vector<int> letters_counts(score.size(), 0);
        map<string,int> words_score;
        int max_sum = 0;

        for (auto i: letters) {
            letters_counts[i - 'a']++;
        }

        for (auto word: words) {
            int tmp_sum = 0;
            bool is_possible=true;
            map<int, int> word_letters_count;

            for (auto letter: word) {
                if (word_letters_count[letter - 'a'] + 1 > letters_counts[letter - 'a']) {
                    is_possible=false;
                    break;
                } else {
                    word_letters_count[letter - 'a']++;
                    tmp_sum += score[letter - 'a'];
                }
            }

            if (is_possible)
                words_score[word] = tmp_sum;
            else
                words_score[word] = 0;
        }

        return max_sum;
    }
};