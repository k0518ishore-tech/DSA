#include <iostream>
#include <cstring>
using namespace std;

class node {
private:
    int vid;
    char vname[20];

public:
    node();
    void getDetails();
    void displayDetails();
    friend class A_Queue;
};
class A_Queue {
private:
    node arr[100];
    int front, rear;
    int capacity;

public:
    A_Queue();
    int enqueue(node);
    node dequeue();
    node peek();
    bool isFull();
    bool isEmpty();
    int size();
    void display();
    void makeQueueEmpty();
    int getFront();
    int getRear();
    ~A_Queue();
};
[24bcs047@mepcolinux ex4..5]$cat app.cpp
#include "head.h"
int main() {
    A_Queue q;
    node n;
    int ch, elt;
    cout << "\n********MENU********\n";
    cout << "1. Enqueue\n2. Dequeue\n3. Peek\n4. isEmpty\n5. isFull\n";
    cout << "6. Size\n7. Display\n8. makeQueueEmpty\n9. Front Index\n";
    cout << "10. Rear Index\n11. Exit\n";

    do {
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                n.getDetails();
                elt = q.enqueue(n);
                if (elt == -1)
                    cout << "Queue is full, cannot enqueue\n";
                break;

            case 2:
                if (!q.isEmpty()) {
                    n = q.dequeue();
                    cout << "Dequeued: ";
                    n.displayDetails();
                } else {
                    cout << "Queue is empty\n";
                }
                break;

            case 3:
                if (!q.isEmpty()) {
                    n = q.peek();
                    cout << "Front element: ";
                    n.displayDetails();
                } else {
                    cout << "Queue is empty\n";
                }
                break;

            case 4:
                cout << (q.isEmpty() ? "Queue is empty\n" : "Queue is not empty\n");
                break;

            case 5:
                cout << (q.isFull() ? "Queue is full\n" : "Queue is not full\n");
                break;

            case 6:
                cout << "Size of Queue: " << q.size() << endl;
                break;

            case 7:
                cout<<"ID\tNAME\n";
                q.display();
                break;

            case 8:
                q.makeQueueEmpty();
                cout << "Queue is now empty\n";
                break;

            case 9:
                cout << "Front Index: " << q.getFront() << endl;
                break;

            case 10:
                cout << "Rear Index: " << q.getRear() << endl;
                break;
        }
    } while (ch != 11);

    return 0;
}
[24bcs047@mepcolinux ex4..5]$cat imp.cpp
#include "head.h"
node::node() {
    vid = -1;
    strcpy(vname, "");
}

void node::getDetails() {
    cout << "Enter GUNID: ";
    cin >> vid;
    cout << "Enter GUNNAME: ";
    cin >> vname;
}

void node::displayDetails() {
    cout << vid << "|" << vname << "\t";
}


A_Queue::A_Queue() {
    front = rear = -1;
    capacity = 5;
}

bool A_Queue::isFull() {
    return rear == capacity - 1;
}

bool A_Queue::isEmpty() {
    return front == -1 || front > rear;
}

int A_Queue::enqueue(node n) {
    if (!isFull()) {
        if (front == -1) front = 0;
        arr[++rear] = n;
        return 1;
    } else {
        return -1;
    }
}

node A_Queue::dequeue() {
    return arr[front++];
}

node A_Queue::peek() {
    return arr[front];
}

int A_Queue::size() {
    if (!isEmpty())
        return rear - front + 1;
    return 0;
}

void A_Queue::display() {
    if (!isEmpty()) {
        for (int i = front; i <= rear; i++)
            arr[i].displayDetails();
    } else {
        cout << "Queue is empty\n";
    }
}

void A_Queue::makeQueueEmpty() {
    front = rear = -1;
}

int A_Queue::getFront() {
    return front;
}

int A_Queue::getRear() {
    return rear;
}

A_Queue::~A_Queue() {
    front = rear = -1;
}