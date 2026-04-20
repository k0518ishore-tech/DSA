#include <iostream>
using namespace std;

class AVLTreeNode {
private:
    int id;
    string name;
    AVLTreeNode *left;
    AVLTreeNode *right;
    int height;

public:
    string getName();
    AVLTreeNode(int val,string n);
    int getData();
    AVLTreeNode* getLeft();
    AVLTreeNode* getRight();
    int getHeight();
    void setData(int val);
    void setLeft(AVLTreeNode* node);
    void setRight(AVLTreeNode* node);
    void setHeight(int h);
};


class AVLTree {
private:
    AVLTreeNode* root;
    int mymax(int a, int b);

public:
    AVLTree();
    AVLTreeNode* RightRotate(AVLTreeNode *k3);
    AVLTreeNode* LeftRotate(AVLTreeNode *k1);
    AVLTreeNode* LRRotate(AVLTreeNode *k3);
    AVLTreeNode* RLRotate(AVLTreeNode *k1);
    AVLTreeNode* insertNode(AVLTreeNode *node, int val,string n);
    AVLTreeNode* deleteNode(AVLTreeNode *node, int val);
    AVLTreeNode* searchNode(AVLTreeNode *node, int val);
    AVLTreeNode* findMinNode(AVLTreeNode *node);
    AVLTreeNode* findMaxNode(AVLTreeNode *node);


    void inorderTraversal(AVLTreeNode *node);
    void preorderTraversal(AVLTreeNode *node);
    void postorderTraversal(AVLTreeNode *node);

    int getHeight(AVLTreeNode *node);
    int BF(AVLTreeNode *node);
    AVLTreeNode* getRoot();
    void setRoot(AVLTreeNode *node);
};

[24bcs047@mepcolinux ex6]$cat i2.cpp
#include"h2.h"
AVLTreeNode::AVLTreeNode(int val,string n) {
    id = val;
    name=n;
    left = right = NULL;
    height = 1;
}
string AVLTreeNode::getName(){
   return name;
}
int AVLTreeNode::getData() {
    return id;
}
AVLTreeNode* AVLTreeNode::getLeft() {
    return left;
}
AVLTreeNode* AVLTreeNode::getRight() {
    return right;
}
int AVLTreeNode::getHeight() {
    return height;
}
void AVLTreeNode::setData(int val) {
    id = val;
}
void AVLTreeNode::setLeft(AVLTreeNode* node) {
    left = node;
}
void AVLTreeNode::setRight(AVLTreeNode* node) {
    right = node;
}
void AVLTreeNode::setHeight(int h) {
    height = h;
}

AVLTree::AVLTree() {
    root = NULL;
}

int AVLTree::mymax(int a, int b) {
    return (a > b) ? a : b;
}

int AVLTree::getHeight(AVLTreeNode *node) {
    return (node == NULL) ? 0 : node->getHeight();
}

int AVLTree::BF(AVLTreeNode *node) {
    return (node == NULL) ? 0 : getHeight(node->getLeft()) - getHeight(node->getRight());
}


AVLTreeNode* AVLTree::RightRotate(AVLTreeNode *k3) {
    AVLTreeNode *k2 = k3->getLeft();
    AVLTreeNode *T2 = k2->getRight();

    k2->setRight(k3);
    k3->setLeft(T2);

    k3->setHeight(1 + mymax(getHeight(k3->getLeft()), getHeight(k3->getRight())));
    k2->setHeight(1 + mymax(getHeight(k2->getLeft()), getHeight(k2->getRight())));
    return k2;
}

AVLTreeNode* AVLTree::LeftRotate(AVLTreeNode *k1) {
    AVLTreeNode *k2 = k1->getRight();
    AVLTreeNode *T2 = k2->getLeft();

    k2->setLeft(k1);
    k1->setRight(T2);

    k1->setHeight(1 + mymax(getHeight(k1->getLeft()), getHeight(k1->getRight())));
    k2->setHeight(1 + mymax(getHeight(k2->getLeft()), getHeight(k2->getRight())));
    return k2;
}

AVLTreeNode* AVLTree::LRRotate(AVLTreeNode *k3) {
    k3->setLeft(LeftRotate(k3->getLeft()));
    return RightRotate(k3);
}

AVLTreeNode* AVLTree::RLRotate(AVLTreeNode *k1) {
    k1->setRight(RightRotate(k1->getRight()));
    return LeftRotate(k1);
}


AVLTreeNode* AVLTree::insertNode(AVLTreeNode *node, int val,string n) {
    if (node == NULL) return new AVLTreeNode(val,n);

    if (val < node->getData())
        node->setLeft(insertNode(node->getLeft(), val,n));
    else if (val > node->getData())
        node->setRight(insertNode(node->getRight(), val,n));
    else
        return node;

    node->setHeight(1 + mymax(getHeight(node->getLeft()), getHeight(node->getRight())));
    int balance = BF(node);

    if (balance > 1 && val < node->getLeft()->getData()) return RightRotate(node);
    if (balance < -1 && val > node->getRight()->getData()) return LeftRotate(node);
    if (balance > 1 && val > node->getLeft()->getData()) return LRRotate(node);
    if (balance < -1 && val < node->getRight()->getData()) return RLRotate(node);

    return node;
}


AVLTreeNode* AVLTree::deleteNode(AVLTreeNode *root, int val) {
    if (root == NULL) return root;

    if (val < root->getData())
        root->setLeft(deleteNode(root->getLeft(), val));
    else if (val > root->getData())
        root->setRight(deleteNode(root->getRight(), val));
    else {
        if (root->getLeft() == NULL || root->getRight() == NULL) {
            AVLTreeNode *temp = root->getLeft() ? root->getLeft() : root->getRight();
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            AVLTreeNode *temp = findMinNode(root->getRight());
            root->setData(temp->getData());
            root->setRight(deleteNode(root->getRight(), temp->getData()));
        }
    }

    if (root == NULL) return root;

    root->setHeight(1 + mymax(getHeight(root->getLeft()), getHeight(root->getRight())));
    int balance = BF(root);

    if (balance > 1 && BF(root->getLeft()) >= 0) return RightRotate(root);
    if (balance > 1 && BF(root->getLeft()) < 0) {
        root->setLeft(LeftRotate(root->getLeft()));
        return RightRotate(root);
    }
    if (balance < -1 && BF(root->getRight()) <= 0) return LeftRotate(root);
    if (balance < -1 && BF(root->getRight()) > 0) {
        root->setRight(RightRotate(root->getRight()));
        return LeftRotate(root);
    }

    return root;
}


AVLTreeNode* AVLTree::searchNode(AVLTreeNode *node, int val) {
    if (node == NULL || node->getData() == val) return node;
    if (val < node->getData()) return searchNode(node->getLeft(), val);
    return searchNode(node->getRight(), val);
}


AVLTreeNode* AVLTree::findMinNode(AVLTreeNode *node) {
    AVLTreeNode *current = node;
    while (current && current->getLeft() != NULL) current = current->getLeft();
    return current;
}

AVLTreeNode* AVLTree::findMaxNode(AVLTreeNode *node) {
    AVLTreeNode *current = node;
    while (current && current->getRight() != NULL) current = current->getRight();
    return current;
}


void AVLTree::inorderTraversal(AVLTreeNode *node) {
    if (node == NULL) return;
    inorderTraversal(node->getLeft());
    cout << node->getData() << "|"<<node->getName()<<"\t";
    inorderTraversal(node->getRight());
}

void AVLTree::preorderTraversal(AVLTreeNode *node) {
    if (node == NULL) return;
    cout << node->getData() << " "<<node->getName()<<"\t";
    preorderTraversal(node->getLeft());
    preorderTraversal(node->getRight());
}

void AVLTree::postorderTraversal(AVLTreeNode *node) {
    if (node == NULL) return;
    postorderTraversal(node->getLeft());
    postorderTraversal(node->getRight());
    cout << node->getData() << "|"<<node->getName()<<"\t";
}


AVLTreeNode* AVLTree::getRoot() {
    return root;
}
void AVLTree::setRoot(AVLTreeNode *node) {
    root = node;
}
[24bcs047@mepcolinux ex6]$cat a2.cpp
#include"h2.h"
int main() {
    AVLTree tree;
    int choice, val;
    string n;

    cout << "\nMenu\n";
    cout << "1.  Insert\n2.  Search\n3.  Inorder \n4.  Preorder \n5.  Postorder \n6.  Find Min\n7.  Find Max\n8.  Exit\n";

    do {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Power to insert: ";
                cin >> val;
                cout<<"Enter Marvel to insert:";
                cin>>n;
                tree.setRoot(tree.insertNode(tree.getRoot(), val,n));
                cout << "Inserted.\n";
                break;
            case 2:
                cout << "Enter id to search: ";
                cin >> val;
                if (tree.searchNode(tree.getRoot(), val))
                    cout << "Found.\n";
                else
                    cout << "Not Found.\n";
                break;
            case 3:
                cout << "Inorder:\n";
                tree.inorderTraversal(tree.getRoot());
                cout << "\n";
                break;
            case 4:
                cout << "Preorder: \n";
                tree.preorderTraversal(tree.getRoot());
                cout << "\n";
                break;
            case 5:
                cout << "Postorder: \n";
                tree.postorderTraversal(tree.getRoot());
                cout << "\n";
                break;
            case 6:
                if (tree.getRoot() != NULL)
                    cout << "Mininum id: " << tree.findMinNode(tree.getRoot())->getData() << "\n";
                else
                    cout << "Tree is empty.\n";
                break;
            case 7:
                if (tree.getRoot() != NULL)
                    cout << "Maximum id: " << tree.findMaxNode(tree.getRoot())->getData() << "\n";
                else
                    cout << "Tree is empty.\n";
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}