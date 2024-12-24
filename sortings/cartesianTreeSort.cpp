#include <vector>
#include <queue>
#include <stack>
#include <memory>

struct Node { // структура на которой завязано все дерево, есть левое поддерево и правое, хранится значение
    int value;
    Node* left;
    Node* right;

    Node(int val) {
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node() {
        delete left;
        delete right;
    }
};

Node* buildCartesianTree(const std::vector<int>& arr) { // работает за O(n) по времени,так же O(n) пространственное
    std::stack<Node*> stack;
    Node* root = nullptr;

    for(auto value: arr) { // проходимся по значениям массива, добавляя их в дерево, N операций
        Node* node = new Node(value);
        Node* last_popped = nullptr;

        while(!stack.empty() && stack.top()->value > value) { // стэк ест мало по времени так как каждый элемент может попасть в стек только один раз
            last_popped = stack.top();
            stack.pop();
        }

        if(!stack.empty()) {
            stack.top()->right = node;
        } else {
            root = node;
        }

        node->left = last_popped;
        stack.push(node);
    }

    return root;
}


std::vector<int> cartesianTreeToSortedArray(Node* root) { // сортировка за O(nlogn)
    // точнее на отсортированных данных будет приближаться к O(n) так как правильно говорить O(n log osc(n))
    std::vector<int> sorted_array;

    auto compare = [](Node* a, Node* b) {
        return a->value > b->value;
    };
    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> min_heap(compare); // используем приоритетную очередь с автосортировкой чтобы брать минимальные элементы
    // O(log N) добавление элемента где N - количество элементов в очереди

    if (root)
        min_heap.push(root);

    while (!min_heap.empty()) { // просто проходимся и сверху вниз засчет свойств нашего дерева берем минимальные
        Node* current = min_heap.top();
        min_heap.pop();

        sorted_array.push_back(current->value);

        if (current->left) {
            min_heap.push(current->left);
        }

        if (current->right) {
            min_heap.push(current->right);
        }
    }

    return sorted_array;
}

void deleteTree(Node* root) {
    delete root; // рекурсивно удаляет все ноды в дереве O(n) временное, чтобы память не утекала просто сделал, плюсы
}

std::vector<int> cartesianSort(const std::vector<int>& arr) { // O(N log N), пространственно O(N)
    Node* root = buildCartesianTree(arr);
    std::vector<int> sorted_arr = cartesianTreeToSortedArray(root);
    deleteTree(root);
    return sorted_arr;
}