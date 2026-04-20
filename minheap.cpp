#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

class node {
private:
    int vid;
    char vname[20];
public:
    node();
    void getdetails();
    void displaydetails();
    friend class MinHeap;
};

class MinHeap {
private:
    int capacity, size;
    node* arr;

public:
    MinHeap(int height);
    ~MinHeap();
    bool isEmpty();
    bool isFull();
    int insertion(node);
    node deleteMin();
    void percolateUp(int idx);
    void percolateDown(int idx);
    void increaseBy(int elt, int val);
    void increaseTo(int elt, int val);
    void decreaseBy(int elt, int val);
    void decreaseTo(int elt, int val);
    void buildHeap(node input[], int n);
    void display();
    void heapSort();
};
[24bcs047@mepcolinux ex7]$cat i1.cpp
#include"h1.h"
node::node() {
    vid = -1;
    strcpy(vname, "");
}

void node::getdetails() {
    cout << "Enter GUNID: ";
    cin >> vid;
    cout << "Enter GUNNAME: ";
    cin >> vname;
}

void node::displaydetails() {
    cout << vid << "|" << vname << "\t";
}

// MinHeap methods
MinHeap::MinHeap(int height) {
    capacity = pow(2, height + 1) - 1;
    arr = new node[capacity];
    size = 0;
}

MinHeap::~MinHeap() {
    delete[] arr;
}

bool MinHeap::isEmpty() {
    return size == 0;
}

bool MinHeap::isFull() {
    return size == capacity;
}

int MinHeap::insertion(node n) {
    if (isFull()) return 0;
    arr[size] = n;
    percolateUp(size);
    size++;
    return 1;
}

void MinHeap::percolateUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (arr[idx].vid < arr[parent].vid) {
            swap(arr[idx], arr[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

void MinHeap::percolateDown(int idx) {
    int smallest = idx;
    while (true) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && arr[left].vid < arr[smallest].vid) smallest = left;
        if (right < size && arr[right].vid < arr[smallest].vid) smallest = right;

        if (smallest != idx) {
            swap(arr[idx], arr[smallest]);
            idx = smallest;
        } else {
            break;
        }
    }
}

node MinHeap::deleteMin() {
    if (isEmpty()) {
        node dummy;
        return dummy;
    }

    node minNode = arr[0];
    arr[0] = arr[size - 1];
    size--;
    percolateDown(0);
    return minNode;
}

void MinHeap::increaseBy(int elt, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i].vid == elt) {
            arr[i].vid += val;
            percolateDown(i);
            return;
        }
    }
}

void MinHeap::increaseTo(int elt, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i].vid == elt) {
            arr[i].vid = val;
            percolateDown(i);
            return;
        }
    }
}

void MinHeap::decreaseBy(int elt, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i].vid == elt) {
            arr[i].vid -= val;
            percolateUp(i);
            return;
        }
    }
}

void MinHeap::decreaseTo(int elt, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i].vid == elt) {
            arr[i].vid = val;
            percolateUp(i);
            return;
        }
    }
}

void MinHeap::buildHeap(node input[], int n) {
    if (n > capacity) n = capacity;
    for (int i = 0; i < n; i++) arr[i] = input[i];
    size = n;
    for (int i = (size / 2) - 1; i >= 0; i--) {
        percolateDown(i);
    }
}

void MinHeap::display() {
    cout << "Heap elements:\n";
    for (int i = 0; i < size; i++) arr[i].displaydetails();
    cout << endl;
}

void MinHeap::heapSort() {
    while (!isEmpty()) {
        node minNode = deleteMin();
        minNode.displaydetails();
    }
    cout << endl;
}
[24bcs047@mepcolinux ex7]$cat a2.cpp
#include"h1.h"
int main() {
    int height, c;
    cout << "Enter heap height: ";
    cin >> height;

    MinHeap heap(height);
    int choice, val, elt;
    cout << "\nMin Heap Menu\n";
    cout << "1. Insert\n2. Remove\n3. Increase By\n4. Increase To\n5. Decrease By\n6. Decrease To\n7. Build Heap\n8. Heap Sort\n9. Display\n10. Exit\n";
    do {

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                node n;
                n.getdetails();
                c = heap.insertion(n);
                if (c == 0)
                    cout << "Heap is full.\n";
                else
                    cout << "Inserted.\n";
                break;
            }
            case 2: {
                node minNode = heap.deleteMin();
                cout << "Deleted Min: ";
                minNode.displaydetails();
                cout << endl;
                break;
            }
            case 3:
                cout << "Enter element and value to increase by: ";
                cin >> elt >> val;
                heap.increaseBy(elt, val);
                break;
            case 4:
                cout << "Enter element and new value: ";
                cin >> elt >> val;
                heap.increaseTo(elt, val);
                break;
            case 5:
                cout << "Enter element and value to decrease by: ";
                cin >> elt >> val;
                heap.decreaseBy(elt, val);
                break;
            case 6:
                cout << "Enter element and new value: ";
                cin >> elt >> val;
                heap.decreaseTo(elt, val);
                break;
            case 7: {
                int n;
                cout << "Enter number of elements: ";
                cin >> n;
                node* arr = new node[n];
                for (int i = 0; i < n; i++) {
                    arr[i].getdetails();
                }
                heap.buildHeap(arr, n);
                heap.display();
                delete[] arr;
                break;
            }
            case 8:
                heap.heapSort();
                break;
            case 9:
                heap.display();
                break;
            case 10:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 10);

    return 0;
}
