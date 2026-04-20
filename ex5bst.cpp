#include<iostream>
using namespace std;
class TreeNode {
    string gun;
    int id;
    TreeNode *left;
    TreeNode *right;

   public:
    TreeNode(int,string);
    ~TreeNode();
    friend class BST;
};

class BST {
    TreeNode *root;

   public:
     BST();
     ~BST();
     TreeNode* getRoot();
     bool isempty();
     bool insertNode(TreeNode* ,TreeNode*);
     TreeNode* deleteNode(TreeNode*,int);
     TreeNode* minValue(TreeNode*);
     void inorder(TreeNode* );
     void preorder(TreeNode* );
     void postorder(TreeNode* );
     TreeNode* search(TreeNode*,int);
     int findMin(TreeNode*);
     int findMax(TreeNode*);

};
[24bcs047@mepcolinux ex5]$cat imp1.cpp
#include"h1.h"
TreeNode::TreeNode(int val,string n) {
   gun= n;
   id = val;
   left=NULL;
   right=NULL;
}

TreeNode::~TreeNode(){
   id =0;
   right=NULL;
   left =NULL;
}

BST::BST() {root =NULL;}

BST::~BST() { root=NULL;}

bool BST::isempty() {return root==NULL;}

TreeNode* BST::getRoot() {return root; }

bool BST::insertNode(TreeNode *temp,TreeNode *newnode) {
   if(root ==NULL){
        root = newnode;
        return 1;
   }
   else{
      if(temp->id<newnode->id){
         if(temp->right==NULL) {
            temp->right=newnode;
            return 1;
         }
         else
            insertNode(temp->right,newnode);
      }
      else if (temp->id>newnode->id){
         if(temp->left==NULL) {
            temp->left=newnode;
            return 1;
         }
         else
            insertNode(temp->left,newnode);
      }
      else
         return 0;
   }
}

TreeNode* BST::deleteNode(TreeNode* temp,int key) {
    if(temp==NULL)
        return temp;
    if(key<temp->id)
        temp->left=deleteNode(temp->left,key);
    else if(key>temp->id)
        temp->right=deleteNode(temp->right,key);
    else{
        if(temp->left==NULL &&temp->right==NULL)
            return NULL;
        else if(temp->left==NULL){
            TreeNode* t=temp->right;
            temp=NULL;
            return t;
        }
        else if(temp->right==NULL){
            TreeNode* t= temp->left;
            temp=NULL;
            return t;
        }

        TreeNode* t =minValue(temp->right);
        temp->id=t->id;
        temp->right=deleteNode(temp->right,t->id);
    }
    return temp;
}

TreeNode* BST::minValue(TreeNode* temp){
    if(temp->left!=NULL)
        minValue(temp->left);
    else
        return temp;
}

void BST::inorder(TreeNode *temp){
   if(temp!=NULL){
      inorder(temp->left);
      cout<<" "<<temp->id<<"|"<<temp->gun<<",";
      inorder(temp->right);
   }
}

void BST::preorder(TreeNode *temp){
   if(temp!=NULL){
      cout<<" "<<temp->id<<"|"<<temp->gun<<",";
      preorder(temp->left);
      preorder(temp->right);
   }
}

void BST::postorder(TreeNode *temp){
   if(temp!=NULL){
      postorder(temp->left);
      postorder(temp->right);
      cout<<" "<<temp->id<<"|"<<temp->gun<<",";
    }
}

TreeNode* BST::search(TreeNode* temp,int key){
        if(temp==NULL ||temp->id ==key)
            return temp;
        else if(temp->id<key)
            search(temp->right,key);
        else if(temp->id>key)
            search(temp->left,key);
}

int BST::findMin(TreeNode* temp){
    if(temp->left!=NULL)
        findMin(temp->left);
    else
        return temp->id;
}

int BST::findMax(TreeNode* temp){
    if(temp->right!=NULL)
        findMax(temp->right);
    else
        return temp->id;
}

[24bcs047@mepcolinux ex5]$cat app.cpp
#include"h1.h"
int main() {
    BST tree;
    string vale;
    int choice, value;
    TreeNode* result;


        cout << "\n\n******* Binary Search Tree Menu *******\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Find Min\n";
        cout << "5. Find Max\n";
        cout << "6. Inorder Traversal\n";
        cout << "7. Preorder Traversal\n";
        cout << "8. Postorder Traversal\n";
        cout << "9. Exit\n";

        do{
           cout<<"\nEnter your choice :";
           cin>>choice;
           switch (choice) {
            case 1:
                cout << "Enter ID to insert: ";
                cin >> value;
                cout <<"Enter the GUN name: ";
                cin>> vale;
                tree.insertNode(tree.getRoot(), new TreeNode(value,vale));
                cout << "Id " << value <<" Gun\t"<<vale<<"\tInserted into the BST.\n";
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                result=tree.deleteNode(tree.getRoot(), value);
                if(result!=NULL)
                    cout<<"Value deleted \n";
                else
                    cout<<"Value is not deleted \n";
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                result = tree.search(tree.getRoot(), value);
                if (result != NULL)
                    cout << value << " found in the BST.\n";
                else
                    cout << value << " not found in the BST.\n";
                break;

            case 4:
                if (!tree.isempty())
                    cout << "Minimum value: " << tree.findMin(tree.getRoot()) << "\n";
                else
                    cout << "Tree is empty!\n";
                break;

            case 5:
                if (!tree.isempty())
                    cout << "Maximum value: " << tree.findMax(tree.getRoot()) << "\n";
                else
                    cout << "Tree is empty!\n";
                break;

            case 6:
                cout << "Inorder Traversal: ";
                tree.inorder(tree.getRoot());
                cout << "\n";
                break;

            case 7:
                cout << "Preorder Traversal: ";
                tree.preorder(tree.getRoot());
                cout << "\n";
                break;

            case 8:
                cout << "Postorder Traversal: ";
                tree.postorder(tree.getRoot());
                cout << "\n";
                break;

            case 9:
                cout << "Exiting program\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
