#include <vector>

using namespace std;

template<typename T>
void cycleSort(vector<T>& array) {
    for (auto cycle_start=0; cycle_start < array.size() - 1; cycle_start++) {
        auto item = array[cycle_start];

        auto pos = cycle_start;
        for (auto i = cycle_start + 1; i < array.size(); i++) {
            if (array[i] < item) {
                pos++;
            }
        }

        if (pos == cycle_start)
            continue;

        while (item == array[pos])
            pos++;

        if (pos != cycle_start)
            swap(item, array[pos]);

        while (pos != cycle_start) {
            pos = cycle_start;
            for (auto i = cycle_start+1; i < array.size(); i++) {
                if (array[i] < item)
                    pos++;
            }

            while (item == array[pos])
                pos++;

            if (item != array[pos])
                swap(item, array[pos]);
        }
    }
}