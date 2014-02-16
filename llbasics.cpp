#include <iostream>
// Following along with:
//     http://cslibrary.stanford.edu/103/LinkedListBasics.pdf

template <typename T>
struct Node {
    T value;
    Node *next = nullptr;
    Node(T v) : value{v} {}
};

Node<int>* buildOneTwoThree() {
    Node<int>* one = new Node<int>(1);
    Node<int>* two = new Node<int>(2);
    Node<int>* three = new Node<int>(3);
    one->next = two;
    two->next = three;

    return one;
}

int main() {
    auto head = buildOneTwoThree();

    std::cout << head->value << '\n';
    std::cout << head->next->value << '\n';
    std::cout << head->next->next->value << '\n';
    std::cout << (head->next->next->next == nullptr) << '\n';
}

