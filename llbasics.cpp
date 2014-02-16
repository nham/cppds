#include <iostream>
// Following along with:
//     http://cslibrary.stanford.edu/103/LinkedListBasics.pdf

template <typename T>
struct Node {
    T value;
    Node *next = nullptr;
    Node(T v) : value{v} {}
    int length() {
        int count = 0;
        for (auto c = this; c != nullptr; c = c->next, ++count);
        return count;
    }
};

template <typename T>
struct LinkedList {
    Node<T> *head = nullptr;
    int n;

    LinkedList() = default;
    LinkedList(Node<T> *n) : head{n}, n{n->length()} {}

    void addFront(T v) {
        auto newhead = new Node<T>(v);
        newhead->next = this->head;
        this->head = newhead;
        this->n += 1;
    }

    T removeFront() {
        auto oldhead = this->head;
        this->head = this->head->next;
        auto val = oldhead->value;
        delete oldhead;
        this->n -= 1;
        return val;
    }
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
    std::cout << "length: " << head->length() << '\n';

    auto list = LinkedList<int>(head);
    std::cout << "size: " << list.n << '\n';
    list.addFront(0);

    std::cout << list.head->value << '\n';
    std::cout << "new size: " << list.n << '\n';

    std::cout << "-------------\n";
    auto list2 = LinkedList<bool>();
    std::cout << list2.n << '\n';
    list2.addFront(true);
    std::cout << list2.n << '\n';
    list2.addFront(false);
    std::cout << list2.n << '\n';
    list2.addFront(true);
    std::cout << list2.n << '\n';
    list2.addFront(false);
    std::cout << list2.n << '\n';

    bool tmp;

    for(int i = 0; i < 4; i++) {
        tmp = list2.removeFront();
        std::cout << "removed " << tmp << ". New size is: " << list2.n << '\n';
    }
}
