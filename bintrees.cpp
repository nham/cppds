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
            return this->left->lookup(v);
        } else {
            return this->right->lookup(v);
        }

    }

    void insert(T v) {
        if (v < value) {
            if (this->left == nullptr) {
                this->left = new Node<T>(v);
            } else {
                this->left->insert(v);
            }
        } else {
            if (this->right == nullptr) {
                this->right = new Node<T>(v);
            } else {
                this->right->insert(v);
            }
        }
    }

    int size() {
        int size = 1;
        if (this->left != nullptr) {
            size += this->left->size();
        }

        if (this->right != nullptr) {
            size += this->right->size();
        }

        return size;
    }
};

template <typename T>
struct BinTree {
    Node<T> *root = nullptr;

    bool lookup(T v) {
        if (root == nullptr) return false;
        return root->lookup(v);
    }

    void insert(T v) {
        if (root == nullptr) {
            root = new Node<T>(v);
        } else {
            root->insert(v);
        }
    }

    int size() {
        if (root == nullptr) return 0;
        return root->size();
    }
};


int main() {
    auto tree = BinTree<int>();
    std::cout << "size: " << tree.size() << '\n';
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);

    std::cout << tree.root->value << '\n';
    std::cout << tree.root->left->value << '\n';
    std::cout << tree.root->right->value << '\n';
    std::cout << "lookup 1: " << tree.lookup(1) << '\n';
    std::cout << "lookup 7: " << tree.lookup(7) << '\n';
    std::cout << "size: " << tree.size() << '\n';
}
