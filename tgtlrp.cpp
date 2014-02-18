// The Great Tree-List Recursion Problem
// http://cslibrary.stanford.edu/109/TreeListRecursion.pdf

#include <tuple>
#include <iostream>

template <typename T>
struct Node {
    T value;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(T v) : value{v} {}

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

// take an ordered binary tree, turn it into a doubly-linked circular list.
// the left pointer becomes *prev, the right pointer becomes *next
// the list must be in increasing order.
template <typename T>
std::tuple<Node<T>*, Node<T>*> treeToList(Node<T> *root, Node<T> *parent) {
    if (root == nullptr) return 
        std::make_tuple(root, root);

    if (root->left == nullptr && root->right == nullptr) 
        return std::make_tuple (root, root);

    Node<T>* minL, *maxL, *minR, *maxR;
    std::tie(minL, maxL) = treeToList(root->left, root);
    std::tie(minR, maxR) = treeToList(root->right, root);

    if (maxL != nullptr)
        maxL->right = root;

    if (minR != nullptr)
        minR->left = root;

    Node<T>* min = minL;
    Node<T>* max = maxR;
    if (min == nullptr)
        min = root;

    if (max == nullptr)
        max = root;

    if (parent == nullptr) {
        min->left = max;
        max->right = min;
    }

    return std::make_tuple(min, max);
}

template <typename T>
void printCircularList(Node<T>* head) {
    if (head == nullptr) return;
    std::cout << head->value << " ";
    for(auto c = head->right; c != head; c = c->right) {
        std::cout << c->value << " ";
    }
    std::cout << '\n';
}


int main() {
    auto tree = Node<int>(4);
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(6);
    tree.insert(5);

    Node<int> *node = nullptr;
    std::tie(node, std::ignore) = treeToList(&tree, node);

    printCircularList(node);

}
