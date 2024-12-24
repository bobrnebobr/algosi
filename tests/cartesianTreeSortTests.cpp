#include <gtest/gtest.h>
#include "../sortings/cartesianTreeSort.cpp"

class CartesianTreeSortTestFixture : public testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(CartesianTreeSortTestFixture, BestCase) {
    std::vector<int> best_case = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    ASSERT_EQ(cartesianSort(best_case), best_case);
}

TEST_F(CartesianTreeSortTestFixture, AverageCase) {
    std::vector<int> average_case = {3, 5, 2, 7, 6, 2, 4, 1};
    std::vector<int> sorted_array = {1, 2, 2, 3, 4, 5, 6, 7};

    ASSERT_EQ(cartesianSort(average_case), sorted_array);
}

TEST_F(CartesianTreeSortTestFixture, WorstCase) {
    std::vector<int> worst_case = {7, 6, 5, 4, 3, 2, 1};
    std::vector<int> sorted_array = {1, 2, 3, 4, 5, 6, 7};

    ASSERT_EQ(cartesianSort(worst_case), sorted_array);
}