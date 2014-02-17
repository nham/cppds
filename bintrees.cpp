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

};

template <typename T>
struct BinTree {
    Node<T> *root = nullptr;

    bool lookup(T v) {
        return BinTree::_lookup(root, v);
    }

    void insert(T v) {
        if (root == nullptr) {
            root = new Node<T>(v);
        } else {
            root->insert(v);
        }
    }

    int size() {
        return BinTree::_size(root);
    }

    int maxDepth() {
        return BinTree::_maxDepth(root);
    }

    void traverse_inorder() {


    }

private:
    static int _maxDepth(Node<T> *node) {
        if (node == nullptr) {
            return 0;
        } else {
            return 1 + std::max(_maxDepth(node->left), _maxDepth(node->right));
        }
    }

    static int _size(Node<T> *node) {
        if (node == nullptr) return 0;
        return 1 + _size(node->left) + _size(node->right);
    }

    static bool _lookup(Node<T> *node, T v) {
        if (node == nullptr) {
            return false;
        } else if (node->value == v) {
            return true;
        } else if (v < node->value) {
            return _lookup(node->left, v);
        } else {
            return _lookup(node->right, v);
        }
    }
};


int main() {
    auto tree = BinTree<int>();
    std::cout << "size: " << tree.size() << '\n';
    std:: cout<< "maxDepth: " << tree.maxDepth() << '\n';
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);

    std::cout << tree.root->value << '\n';
    std::cout << tree.root->left->value << '\n';
    std::cout << tree.root->right->value << '\n';
    std::cout << "lookup 1: " << tree.lookup(1) << '\n';
    std::cout << "lookup 7: " << tree.lookup(7) << '\n';
    std::cout << "size: " << tree.size() << '\n';
    std:: cout<< "maxDepth: " << tree.maxDepth() << '\n';
    tree.insert(5);
    tree.insert(7);
    std::cout << "size: " << tree.size() << '\n';
    std:: cout<< "maxDepth: " << tree.maxDepth() << '\n';
}
