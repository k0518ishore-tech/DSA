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
    friend class MaxHeap;
};

class MaxHeap {
private:
    int capacity, size;
    node* arr;

public:
    MaxHeap(int height);
    ~MaxHeap();
    bool isEmpty();
    bool isFull();
    int insertion(node);
    node deleteMax();
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

[24bcs047@mepcolinux ex7]$cat i2.cpp
#include"h2.h"
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

// MaxHeap methods
MaxHeap::MaxHeap(int height) {
    capacity = pow(2, height + 1) - 1;
    arr = new node[capacity];
    size = 0;
}

MaxHeap::~MaxHeap() {
    delete[] arr;
}

bool MaxHeap::isEmpty() {
    return size == 0;
}

bool MaxHeap::isFull() {
    return size == capacity;
}

int MaxHeap::insertion(node n) {
    if (isFull()) return 0;
    arr[size] = n;
    percolateUp(size);
    size++;
    return 1;
}

void MaxHeap::percolateUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (arr[idx].vid > arr[parent].vid) {
            swap(arr[idx], arr[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

void MaxHeap::percolateDown(int idx) {
    int largest = idx;
    while (true) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && arr[left].vid > arr[largest].vid) largest = left;
        if (right < size && arr[right].vid > arr[largest].vid) largest = right;

        if (largest != idx) {
            swap(arr[idx], arr[largest]);
            idx = largest;
        } else {
            break;
        }
    }
}

node MaxHeap::deleteMax() {
    if (isEmpty()) {
        node dummy;
        return dummy;
    }

    node maxNode = arr[0];
    arr[0] = arr[size - 1];
    size--;
    percolateDown(0);
    return maxNode;
}

void MaxHeap::increaseBy(int elt, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i].vid == elt) {
            arr[i].vid += val;
            percolateUp(i);
            return;
        }
    }
}

void MaxHeap::increaseTo(int elt, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i].vid == elt) {
            arr[i].vid = val;
            percolateUp(i);
            return;
        }
    }
}

void MaxHeap::decreaseBy(int elt, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i].vid == elt) {
            arr[i].vid -= val;
            percolateDown(i);
            return;
        }
    }
}

void MaxHeap::decreaseTo(int elt, int val) {
    for (int i = 0; i < size; i++) {
        if (arr[i].vid == elt) {
            arr[i].vid = val;
            percolateDown(i);
            return;
        }
    }
}

void MaxHeap::buildHeap(node input[], int n) {
    if (n > capacity) n = capacity;
    for (int i = 0; i < n; i++) arr[i] = input[i];
    size = n;
    for (int i = (size / 2) - 1; i >= 0; i--) {
        percolateDown(i);
    }
}

void MaxHeap::display() {
    cout << "Heap elements:\n";
    for (int i = 0; i < size; i++) arr[i].displaydetails();
    cout << endl;
}

void MaxHeap::heapSort() {
    while (!isEmpty()) {
        node maxNode = deleteMax();
        maxNode.displaydetails();
    }
    cout << endl;
}

[24bcs047@mepcolinux ex7]$cat a1.cpp
#include"h2.h"
int main() {
    int height, c;
    cout << "Enter heap height: ";
    cin >> height;

    MaxHeap heap(height);
    int choice, val, elt;
    cout << "\nMax Heap Menu\n";
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
                node maxNode = heap.deleteMax();
                cout << "Deleted Max: ";
                maxNode.displaydetails();
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
