// http://cslibrary.stanford.edu/110/BinaryTrees.pdf
#include <iostream>
#include <string>

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
        BinTree::_traverse_inorder(root);
    }

    bool hasPathSum(T v) {
        return BinTree::_hasPathSum(root, v);
    }

    void printPaths() {
        std::string x = "";
        BinTree::_printPaths(root, x);
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

    static void _traverse_inorder(Node<T> *node) {
        if (node == nullptr) {
            return;
        } else {
            _traverse_inorder(node->left);
            std::cout << node->value << ' ';
            _traverse_inorder(node->right);
        }
    }

    static bool _hasPathSum(Node<T> *node, int sum) {
        // strategy: enumerate all root-to-leaf paths (or rather the sum of 
        // the r-t-l paths) and check
        if (node == nullptr) {
            return sum == 0;
        } else {
            sum -= node->value;
            return _hasPathSum(node->left, sum) || _hasPathSum(node->right, sum);
        }
    }

    static void _printPaths(Node<T> *node, std::string const& path) {
        if (node == nullptr) {
            return;
        } 

        std::string x = path + std::to_string(node->value) + " ";
        
        if (node->left == nullptr && node->right == nullptr) {
            std::cout << "Path: " << x << '\n';
        } else {
            _printPaths(node->left, x);
            _printPaths(node->right, x);
        }

    }
};


int main() {
    auto tree = BinTree<int>();
    std::cout << "size: " << tree.size() << '\n';
    std:: cout<< "maxDepth: " << tree.maxDepth() << '\n';
    std::cout << "traverse in order: ";
    tree.traverse_inorder();
    std:: cout << '\n';

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
    std::cout << "maxDepth: " << tree.maxDepth() << '\n';

    std::cout << "traverse in order: ";
    tree.traverse_inorder();
    std:: cout << '\n';

    std::cout << "hasPathSum\n";
    std::cout << tree.hasPathSum(3) << '\n';
    std::cout << tree.hasPathSum(4) << '\n';
    std::cout << tree.hasPathSum(17) << '\n';

    tree.printPaths();
    tree.insert(4);
    std::cout << "after insert(4):\n";
    tree.printPaths();
}
