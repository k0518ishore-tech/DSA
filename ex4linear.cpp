#include<iostream>
using namespace std;
class Node {
    public:
        int id;
        string name;
        Node *next;
    public:
        Node(int,string);
        Node(const Node &);
        friend class L_list;
        ~Node();
};
class L_queue {
        Node *head;
    public:
        L_queue();
        ~L_queue();
        int isEmpty();
        void display();
        int makeQueueEmpty();
        int enqueue(Node*);
        int dequeue();
        int peek();
        int size();
};
[24bcs047@mepcolinux ex4]$cat imp4.cpp
#include"head4.h"
Node::Node(int i,string n) {
    id=i;
    name=n;
    next = NULL;
}

Node::~Node() {
    id=0;
    name="";
    next=NULL;
}

L_queue::L_queue () {
    head = NULL;
}

int L_queue::isEmpty() {
    return head==NULL;
}

int L_queue::enqueue(Node* newnode){
    if(isEmpty())
        head=newnode;
    else{
        Node* temp=head;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=newnode;
    }
    return 1;
}

int L_queue::dequeue(){
    if(isEmpty())
        return -1;
    Node* temp=head;
    head=head->next;
    int dlt=temp->id;
    delete temp;
    temp = NULL;
    return dlt;
}

int L_queue::peek(){
    cout<<"Top GAME ID : "<<head->name<<endl;
}

int L_queue::size(){
    int count=0;
    Node* temp=head;
    while(temp!=NULL){
        count++;
        temp=temp->next;
    }
    return count;
}

void L_queue::display(){
    Node* temp=head;
    cout<<"***************************\n";
    cout<<"LEVEL      NAME\n";
    while(temp!=NULL){
    cout<<temp->id<<"    "<<temp->name<<endl;
        temp=temp->next;
    }
    cout<<"***************************\n";
}

int L_queue::makeQueueEmpty(){
    while(!isEmpty())
        int element=dequeue();
}

L_queue::~L_queue(){
    delete head;
    head =NULL;
}

[24bcs047@mepcolinux ex4]$cat app4.cpp
#include"head4.h"
int main() {
    L_queue queue;

    int choice;
    int element;
    int id;
    string name;

    cout<<"\nMENU \n1:enqueue \n2:dequeue \n3:peek \n4:isempty \n5:isfull \n6:size \n7:display \n8:makequeueempty \n9:exit";
    do {
        cout<<"\nEnter your choice:";
        cin >> choice;

        switch (choice) {
            case 1:{
                cout << "Enter GAME ID NAME: ";
                cin>>name;
                cout<<"Enter id:";
                cin>>id;
                Node* newnode= new Node(id,name);
                element=queue.enqueue(newnode);
                if(element==-1) {
                    cout<<"queue is full, cannot enqueue";
                }
                break;
            }
            case 2: {
                element = queue.dequeue();
                if (element !=1) {
                    cout << "dequeue Game id  : "<<element<<endl;
                }
                else{
                    cout<<"queue is empty, cannot dequeue";
                }
                break;
            }
            case 3: {
                element = queue.peek();
                break;
            }
            case 4:{
                if (queue.isEmpty()) {
                    cout << "queue is empty." << endl;
                } else {
                    cout << "queue is not empty." << endl;
                }
                break;
            }
            case 6: {
                cout << "Current queue size: " << queue.size() << endl;
                break;
            }
            case 7: {
                queue.display();
                break;
            }
            case 8: {
                queue.makeQueueEmpty();
                cout<<"queue is now empty";
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