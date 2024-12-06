#include <vector>
#include <limits>

using namespace std;

template<typename T = int>
struct TournamentTreeNode {
    T value;
    int index;
};

template<typename T = int>
TournamentTreeNode<T> tournament(TournamentTreeNode<T> a, TournamentTreeNode<T> b) {
    return (a.value < b.value) ? a : b;
}

template<typename T>
vector<T> tournamentSort(const vector<T>& array) {
    int n = array.size();
    if (n == 0) return {};

    vector<TournamentTreeNode<T>> tree(2 * n - 1);

    for (int i = 0; i < n; i++) {
        tree[n - 1 + i] = {array[i], i};
    }

    for (int i = n - 2; i >= 0; i--) {
        tree[i] = tournament(tree[2 * i + 1], tree[2 * i + 2]);
    }

    vector<T> sortedArr(n);

    for (int i = 0; i < n; i++) {
        int winnerIndex = tree[0].index;
        sortedArr[i] = array[winnerIndex];
        int current = n - 1 + winnerIndex;

        tree[current] = {numeric_limits<T>::max(), winnerIndex};

        while (current > 0) {
            int parent = (current - 1) / 2;
            int leftChild = 2 * parent + 1;
            int rightChild = 2 * parent + 2;

            if (rightChild < tree.size()) {
                tree[parent] = tournament(tree[leftChild], tree[rightChild]);
            } else {
                tree[parent] = tree[leftChild];
            }

            current = parent;
        }
    }

    return sortedArr;
}