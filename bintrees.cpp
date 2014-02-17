// http://cslibrary.stanford.edu/110/BinaryTrees.pdf
#include <iostream>

template <typename T>
struct Node {
    T value;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(T v) : value{v} {}

    bool lookup(T v) {
        if (this == nullptr) {
            return false;
        } else if (this->value == v) {
            return true;
        } else if (v < this->value) {
            return lookup(this->left);
        } else {
            return lookup(this->right);
        }

    }
};

template <typename T>
struct BinTree {
    Node<T> *root = nullptr;


    void insert(T v) {
        if (root == nullptr) {
            root = new Node<T>(v);
        } else if (v < root->value) {
            root->left->insert(v);
        } else {
            root->right->insert(v);
        }

    }
};


int main() {
    auto tree = BinTree<int>();
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);

    std::cout << tree.root->value << '\n';
    std::cout << tree.root->left->value << '\n';
    std::cout << tree.root->right->value << '\n';
}
