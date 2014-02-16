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
struct SLList {
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    int n;

    SLList() = default;
    SLList(Node<T> *n) {
        this->head = n;
        auto c = n;
        int count = 0;
        for(; c->next != nullptr; c = c->next, ++count);
        this->tail = c;
        this->n = count + 1;
    }

    void add_first(T v) {
        auto newhead = new Node<T>(v);
        newhead->next = this->head;
        this->head = newhead;

        if (n == 0) {
            this->tail = newhead;
        }
        this->n += 1;
    }

    T remove_first() {
        auto oldhead = this->head;
        this->head = this->head->next;
        auto val = oldhead->value;
        delete oldhead;

        if (n == 1) {
            this->tail = nullptr;
        }
        this->n -= 1;
        return val;
    }

    void add_last(T v) {
        auto newtail = new Node<T>(v);
        this->tail->next = newtail;
        this->tail = newtail;

        if (n == 0) {
            this->head = newtail;
        }
        this->n += 1;
    }

    void print() {
        if (this->n == 0) {
            std::cout << '\n';
            return;
        }

        std::cout << this->head->value;
        for (auto c = this->head->next; c != nullptr; c = c->next) {
            std::cout << " -> " << c->value;
        }
        std::cout << '\n';
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

    auto list = SLList<int>(head);
    std::cout << "New SLList size: ";
    list.print();

    list.add_first(0);
    std::cout << "after add_first(0): ";
    list.print();

    list.add_last(4);
    std::cout << "after add_last(4): ";
    list.print();

    std::cout << "\n-------------\n";
    auto list2 = SLList<bool>();
    list2.print();
    list2.add_first(true);
    list2.print();
    list2.add_first(false);
    list2.print();
    list2.add_first(true);
    list2.print();
    list2.add_first(false);
    list2.print();


    list2.remove_first();
    list2.print();
    list2.remove_first();
    list2.print();
    list2.add_last(true);
    list2.print();
    list2.remove_first();
    list2.print();
}
