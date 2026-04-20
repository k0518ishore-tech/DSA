#include<iostream>
using namespace std;
class Node {
    public:
        int data;
        Node *next;
    public:
        Node(int);
        Node(const Node &);
        friend class L_list;
        ~Node();
};
class L_Stack {
        Node *top;
    public:
        L_Stack();
        int isEmpty();
        void display();
        int makeStactEmpty();
        int push(Node*);
        int pop();
        int peek();
        int size();
};

[24bcs047@mepcolinux ex3]$cat im.cpp
#include"header.h"
Node::Node(int val) {
    data = val;
    next = NULL;
}

Node::Node(const Node &other){
    data=other.data;
    next=other.next;
}

Node::~Node() {
    data=-1;
    next = NULL;
}
L_Stack::L_Stack () {
    top = NULL;
}

int L_Stack::isEmpty() {
    return top==NULL;
}

int L_Stack::push(Node* newnode) {
    if(isEmpty())
        top=newnode;
    else{
        newnode->next=top;
        top=newnode;
    }
    return 1;
}

int L_Stack::pop() {
    if (isEmpty())
        return -1;
    Node* temp= top;
    int element= top->data;
    top=top->next;
    delete temp;
    temp=NULL;
    return element;
}

int L_Stack::peek(){
    if(!isEmpty())
        return top->data;
    else
        return -1;
}

int L_Stack::size() {
    int count=0;
    Node* temp=top;
    while(temp!=NULL) {
        count++;
        temp=temp->next;
    }
    return count;
}

int L_Stack::makeStactEmpty(){
    Node* temp=top;
    while(top!=NULL) {
        top = top->next;
        delete temp;
        temp=top;
    }
}

void L_Stack::display() {
    Node* temp=top;
    while(temp!=NULL) {
        cout<<temp->data<<"  ";
        temp=temp->next;
    }
}

[24bcs047@mepcolinux ex3]$cat app1.cpp
#include"header.h"
int main() {
    L_Stack stack;

    int choice;
    int element;
    cout<<"\nMENU \n1:push \n2:pop \n3:peek \n4:isempty \n5:isfull \n6:size \n7:display \n8:makestackempty \n9:exit ";

    do {
        cout<<"Enter your choice:";
        cin >> choice;

        switch (choice) {
            case 1:{
                cout << "Enter the element to push: ";
                cin >> element;
                Node* newnode= new Node(element);
                element=stack.push(newnode);
                if(element==-1) {
                    cout<<"Stack is full, cannot push elements";
                }
                break;
            }
            case 2: {
                element = stack.pop();
                if (element ==1) {
                    cout << "Popped element: " << element << endl;
                }
                else if (element==-1){
                    cout<<"Stack is empty, cannot pop elements";
                }
                break;
            }
            case 3: {
                element = stack.peek();
                if (element != -1) {
                    cout << "Top element: " << element << endl;
                }
                break;
            }
            case 4:{
                if (stack.isEmpty()) {
                    cout << "Stack is empty." << endl;
                } else {
                    cout << "Stack is not empty." << endl;
                }
                break;
            }
            case 6: {
                cout << "Current stack size: " << stack.size() << endl;
                break;
            }
            case 7: {
                stack.display();
                break;
            }
            case 8: {
                stack.makeStactEmpty();
                cout<<"Stack is now empty";
                break;
            }
            case 9: {
                cout << "Exiting..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

     return 0;
}