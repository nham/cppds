#include <iostream>
// Following along with:
//     http://cslibrary.stanford.edu/103/LinkedListBasics.pdf
// this also solves problems in:
//     http://cslibrary.stanford.edu/105/LinkedListProblems.pdf

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

    void append(SLList *list) {
        this->n += list->n;
        this->tail->next = list->head;
        this->tail = list->tail;
    }

    // iterative reverse
    void reverse_iter() {
        if (this->n == 0) return;

        this->tail = this->head;
        auto c = this->head;
        Node<T> *rev = nullptr;
        Node<T> *tmp = nullptr;
        while (c != nullptr) {
            tmp = c->next;
            c->next = rev;
            rev = c;
            c = tmp;
        }
        this->head = rev;
    }

    void reverse_rec() {
        if (this->n == 0) return;
        auto tmp = this->tail;
        this->tail = reverse_rec(this->head);
        this->head = tmp;
    }

    T getNth(int n) {
        auto c = this->head;
        for (int i = 0; i < n; c = c->next, ++i);
        return c->value;
    }

    void insertNth(T v, int n) {
        auto c = this->head;
        for (int i = 0; i < n-1; c = c->next, ++i);
        auto node = new Node<T>(v);
        node->next = c->next;
        c->next = node;
        this->n += 1;
    }

    // removes all nodes
    void clear() {
        int size = this->n;
        for (int i = 0; i < size; ++i) {
            this->remove_first();
        }
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

    private:
        Node<T>* reverse_rec(Node<T> *node) {
            if (node == nullptr || node->next == nullptr) return node;

            auto tail = reverse_rec(node->next);
            node->next = nullptr;
            tail->next = node;
            return node;
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

// number of occurrences of v in n
template <typename T>
int count(Node<T> *n, T v) {
    int count = 0;
    for (auto c = n; c != nullptr; c = c->next) {
        if (c->value == v) {
            count += 1;
        }
    }
    return count;
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

    std::cout << "number of fives: " << count(list.head, 5) << '\n';
    std::cout << "number of fours: " << count(list.head, 4) << '\n';

    std::cout << "getNth(3): " << list.getNth(3) << '\n';

    list.insertNth(7, 3);
    std::cout << "after insertNth(7, 3): ";
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

    std::cout << "number of trues: " << count(list2.head, true) << '\n';
    std::cout << "getNth(2): " << list2.getNth(2) << '\n';


    list2.remove_first();
    list2.print();
    list2.remove_first();
    list2.print();
    list2.add_last(true);
    list2.print();
    list2.remove_first();
    list2.print();


    auto list3 = SLList<int>();
    list3.add_first(8);
    list3.add_first(13);
    list3.add_first(21);
    list3.print();

    list3.append(&list);
    list3.print();

    list3.reverse_iter();
    list3.print();

    list3.reverse_rec();
    list3.print();

    list3.clear();
    std::cout << "list3 after clear(): ";
    list3.print();

    auto list4 = SLList<int>();
    list4.add_first(1);
    list4.add_first(2);
    list4.print();
    list4.reverse_rec();
    list4.print();
}
