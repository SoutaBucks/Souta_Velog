#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Node {
    Node * parent;
    Node * left, * right;
    int value;
    Node(int _v) : value(_v), parent(NULL), left(NULL), right(NULL) {}
};

class LinkedBinaryTree {
private:
    Node * root;

public:
    LinkedBinaryTree() {
        root = NULL;
    }

    Node * getRoot() {
        return root;
    }

    // 특정 node가 left-child라면 1 아니면 0
    bool isLeftChild(Node * node) {
        return node->parent->left->value == node->value;
    }

    // 특정 node가 right-child라면 1 아니면 0
    bool isRightChild(Node * node) {
        return node->parent->right->value == node->value;
    }

    //isRoot - Root라면 1 아니면 0
    bool isRoot(Node * node) {
        return node->parent == nullptr;
    }

    bool isExternal(Node * node) {
        return (node->left == NULL) && (node->right == NULL);
    }

    // insert method - node를 child로 삽입
    void insert(int value) {
        Node * newNode = new Node(value);
        Node *here = root;

        // Root가 존재하지 않는경우
        if(root == NULL) {
            root = new Node(value);
            return;
        }
        // value가 이미 존재하는 경우
        else if(find(value)) {
            cout << value << " is already in Binary Tree" << endl;
            return;
        }
        // Root가 존재하는 경우
        else {
            while (true) {
                if (here->value < newNode->value) {
                    if(here->right == NULL) {
                        here->right = newNode;
                        newNode->parent = here;
                        break;
                    }
                    here = here->right;
                }
                else {
                    if(here->left == NULL) {
                        here->left = newNode;
                        newNode->parent = here;
                        break;
                    }
                    here = here->left;
                }
            }
        }
    }

    // remove method - node를 제거
    void remove(int value) {

        Node * foundNode = find(value);

        if(!foundNode) {
            cout << "There is no Node" << endl;
        }
        else {
            // 1. leaf-node인 경우
            if(isExternal(foundNode)) {
                if(isLeftChild(foundNode)) {
                    foundNode->parent->left = NULL;
                    foundNode->parent = NULL;
                }
                else {
                    foundNode->parent->right = NULL;
                    foundNode->parent = NULL;
                }
            }
            // 2. left-child만 있는 경우
            else if(foundNode->right == NULL && foundNode->left != NULL) {
                foundNode->left->parent = foundNode->parent;
                if(isLeftChild(foundNode))
                    foundNode->parent->left = foundNode->left;
                else
                    foundNode->parent->right = foundNode->left;
            }
            // 3. right-child만 있는 경우
            else if(foundNode->right != NULL && foundNode->left == NULL) {
                foundNode->right->parent = foundNode->parent;
                if(isLeftChild(foundNode))
                    foundNode->parent->left = foundNode->right;
                else
                    foundNode->parent->right = foundNode->right;
            }
            // 4. 둘 다 있는 경우
            else {
                Node * theMinNode = foundNode->right;
                while(theMinNode->left != NULL)
                    theMinNode = theMinNode->left;
                if(theMinNode->right != NULL) {
                    theMinNode->right->parent = theMinNode->parent;
                    theMinNode->parent->left = theMinNode->right;
                }
                theMinNode->parent = foundNode->parent;
                theMinNode->left = foundNode->left;
                if(isLeftChild(foundNode))
                    foundNode->parent->left = theMinNode;
                else
                    foundNode->parent->right = theMinNode;
            }
        }
    }

    // find method - 해당 node를 찾으면 node 반환 아니면 NULL
    Node * find(int value) {
        Node * here = root;
        while(true) {
            if(here->value < value)
                here = here->right;
            else
                here = here->left;

            if(here == NULL)    return NULL;
            if(here->value == value)    return here;
        }
    }

    // 전위순회
    void preorder(Node * here) {
        if(here == NULL)    return;

        cout << here->value << " ";
        preorder(here->left);
        preorder(here->right);
    }

    // 중위순회
    void inorder(Node * here) {
        if(here == NULL)    return;

        inorder(here->left);
        cout << here->value << " ";
        inorder(here->right);
    }

    // 후위순회
    void postorder(Node * here) {
        if(here == NULL)    return;

        postorder(here->left);
        postorder(here->right);
        cout << here->value << " ";
    }
};

int main() {
    LinkedBinaryTree * linkedBinaryTree = new LinkedBinaryTree();
    Node * root = linkedBinaryTree->getRoot();
    linkedBinaryTree->insert(10);
    linkedBinaryTree->insert(20);
    linkedBinaryTree->insert(5);
    linkedBinaryTree->insert(7);
    linkedBinaryTree->insert(2);
    linkedBinaryTree->insert(1);
    linkedBinaryTree->insert(30);
    linkedBinaryTree->remove(20);
    linkedBinaryTree->preorder(linkedBinaryTree->getRoot());

}
