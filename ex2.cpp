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

class L_list {
        Node *head;
    public:
        L_list();
        int isEmpty();
        void display();
        void makeListEmpty();
        int insertAtFirst(Node *);
        int insertAtLast(Node *);
        int insertByPos(int,Node*);
        int insertBeforeAnElt(int,int);
        int deleteAtFirst();
        int deleteAtLast();
        int deleteByPos(int);
        int deleteBeforeAnElt(int);
        Node *searchByValue(int);
        Node *searchByPos(int);
};

[24bcs047@mepcolinux ex2]$cat imp.cpp
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

L_list::L_list () {
    head = NULL;
}

void L_list::display() {
    Node *temp = head;
    while(temp != NULL) {
        cout<<temp->data<<"\t";
        temp=temp->next;
    }
}

int L_list::isEmpty() {
    return head == NULL;
}

int L_list::insertAtFirst(Node * newnode){
    if (isEmpty())
        head = newnode ;
    else {
        newnode->next = head;
        head = newnode;
    }
    return 1;
}

int L_list::insertAtLast(Node * newnode) {
    if (isEmpty())
        head = newnode;
    else {
        Node *temp = head;
        while(temp->next != NULL)
            temp=temp->next;
        temp->next=newnode;
    }
    return 1;
}

int L_list::deleteAtFirst() {
    if (isEmpty())
        return 0;
    else {
        Node *temp= head;
        head = head->next;
        delete temp;
    }
    return  1;
}

int L_list::deleteAtLast() {
    if (isEmpty())
        return 0;
    else {
        Node *current = head;
        Node *previous= NULL;
        while(current->next != NULL) {
            previous = current;
            current=current->next;
        }
        previous->next=NULL;
        delete current;
        current= NULL;
        return 1;
    }
}

Node * L_list::searchByValue(int value) {
    Node *temp= head;
    while(temp!=NULL) {
        if(temp->data == value)
            return temp;
        temp=temp->next;
    }
    return NULL;
}

Node* L_list::searchByPos(int position) {
    if(position<1)
        return 0;

    Node *temp=head;
    int currentPosition=1;
    while(temp!=NULL && currentPosition<position) {
        if(currentPosition==position)
            return temp;
        temp=temp->next;
        currentPosition++;
    }
    if(currentPosition==position)
        return temp;
    else
        return NULL;
}

void L_list::makeListEmpty() {
    Node* current = head;
    Node* previous=NULL;
    while(current!=NULL) {
        previous=current;
        current=current->next;
        delete previous;
    }
    head = NULL;
}

int L_list::insertByPos(int position,Node* newnode) {
    if(position<1)
        return 0;
    if(position==1) {
        if (isEmpty())
            head = newnode ;
        else {
            newnode->next = head;
            head = newnode;
    }
    }
    else{
        Node* current = head;
        Node* previous =NULL;
        int currentposition=1;
        while(current!=NULL && currentposition<position) {
            previous=current;
            current=current->next;
            currentposition++;
        }
        if(currentposition==position){
            if(previous!=NULL){
                previous->next =newnode;
                newnode->next=current;
            }
            return 1;
        }
        else
            return 0;
    }
}

int L_list::deleteByPos(int position) {
    if(position<1)
        return 0;
    if(position==1){
        if (isEmpty())
            return 0;
        else {
            Node *temp= head;
            head = head->next;
            delete temp;
    }
    return  1;
    }
    else {
        Node* current= head;
        Node* previous= NULL;
        int currentposition=1;
        while(current!=NULL && currentposition<position) {
            previous=current;
            current=current->next;
            currentposition++;
        }
        if(currentposition==position){
            if(previous!=NULL) {
                previous->next=current->next;
                delete current;
            }
            return 1;
        }
        else
        return 0;
    }
}

int L_list::insertBeforeAnElt(int element, int value) {
    int result,position=1;
    Node *n,*temp= head;
    if(isEmpty())
        return 0;
    if(head->data==element){
        n= new Node(value);
        result=insertAtFirst(n);
        return result;
    }
    while(temp!=NULL) {
        if(temp->data == element){
            n= new Node(value);
            result= insertByPos(position,n);
            return result;
        }
        temp=temp->next;
        position++;
    }
    return 0;
}


int L_list::deleteBeforeAnElt(int element) {
    int result,position=1;
    Node *temp= head;
    if(isEmpty())
        return 0;
    if(head->data==element){
        return 0;
    }
    while(temp!=NULL) {
        if(temp->data == element){
            result= deleteByPos(position-1);
            return result;
        }
        temp=temp->next;
        position++;
    }
    return 0;
}

[24bcs047@mepcolinux ex2]$cat app.cpp
#include"header.h"
int main() {
    L_list list;
    int ch, value, position, element;
    Node* newNode = NULL;

        cout<<"\nMENU";
        cout << "\n1. Insert at First \n2. Insert at Last \n3. Insert by Position \n4. Insert Before an Element \n5. Delete at First \n6. Delete at Last \n7. Delete by Position \n8. Delete Before an Element \n9. Search by Value \n10. Search by Position \n11. Display List \n12. Make List Empty \n13. Check if List is Empty \n0. Exit" << endl;
       do {
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:{
                cout << "Enter value to insert: ";
                cin >> value;
                newNode = new Node(value);
                if (list.insertAtFirst(newNode)) {
                    cout << "Node inserted at the beginning." << endl;
                }
                break;
                   }
            case 2:{
                cout << "Enter value to insert: ";
                cin >> value;
                newNode = new Node(value);
                if (list.insertAtLast(newNode)) {
                    cout << "Node inserted at the end." << endl;
                }
                break;
                   }
            case 3:{
                cout << "Enter position to insert at: ";
                cin >> position;
                cout << "Enter value to insert: ";
                cin >> value;
                newNode = new Node(value);
                if (list.insertByPos(position, newNode)) {
                    cout << "Node inserted at position " << position << "." << endl;
                } else {
                    cout<<"Node not inserted";
                }
                break;
                   }
            case 4:{
                cout << "Enter the element value to insert before: ";
                cin >> element;
                cout << "Enter value of new node: ";
                cin >> value;
                if (list.insertBeforeAnElt(element, value)) {
                    cout << "Node with value " << value << " inserted before " << element << "." << endl;
                }
                else
                    cout<<"Node not inserted";
                break;
                   }
            case 5:{
                if (list.deleteAtFirst()) {
                    cout << "First node deleted." << endl;
                } else {
                    cout << "List is empty, cannot delete." << endl;
                }
                break;
                   }
            case 6:{
                if (list.deleteAtLast()){
                    cout << "node deleted " << endl;
                }
                else{
                   cout<<"list is empty "<<endl;
                }
                break;}
            case 7:{
                cout << "Enter position to delete: ";
                cin >> position;
                if (list.deleteByPos(position)) {
                    cout << "Node at position " << position << " deleted." << endl;
                }
                cout<<"Node not deleted";
                break;
                   }
            case 8:{
                cout << "Enter the element value to delete before: ";
                cin >> element;
                if (list.deleteBeforeAnElt(element)) {
                    cout << "Node before " << element << " deleted." << endl;
                }
                else
                    cout<<"Node not deleted";
                break;
                   }
            case 9:{
                cout << "Enter value to search: ";
                cin >> value;
                if (list.searchByValue(value)) {
                    cout << "Element " << value << " found in the list." << endl;
                } else {
                    cout << "Element " << value << " not found in the list." << endl;
                }
                break;
                   }
            case 10:{
                cout << "Enter position to search: ";
                cin >> position;
                if (list.searchByPos(position)) {
                    cout << "Node found at position " << position << "." << endl;
                } else {
                    cout << "No node found at position " << position << "." << endl;
                }
                break;
                    }
            case 11:{
                list.display();
                break;
                    }
            case 12:{
                list.makeListEmpty();
                cout << "List has been cleared." << endl;
                break;
                    }
            case 13:{
                if (list.isEmpty()) {
                    cout << "The list is currently empty." << endl;
                } else {
                    cout << "The list is not empty." << endl;
                }
                break;
                    }
            case 0:{
                cout << "Exiting program. " << endl;
                break;
                   }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (ch != 0);

    return 0;
}