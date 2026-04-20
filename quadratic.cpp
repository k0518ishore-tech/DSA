#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    int id;
    string name;
    Node();
    Node(int i, string n);
    void displayNode();
};

class HashTable {
    Node* table;
    int tableSize;
    int currentSize;
public:
    HashTable(int size);
    ~HashTable();
    int hashFunction(int key);
    void insertItem(Node item);
    bool searchItem(int key);
    void displayHash();
};

[24bcs047@mepcolinux ouadrattic]$cat imp.pp
cat: imp.pp: No such file or directory
[24bcs047@mepcolinux ouadrattic]$cat imp.cpp
#include "head.h"
Node::Node() {
    id = 0;
    name = "";
}

Node::Node(int i, string n) {
    id = i;
    name = n;
}

void Node::displayNode() {
    cout << "[" << id << " - " << name << "]";
}

HashTable::HashTable(int size) {
    tableSize = size;
    currentSize = 0;
    table = new Node[tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i].id = -1;
        table[i].name = "";
    }
}

HashTable::~HashTable() {
    delete[] table;
}

int HashTable::hashFunction(int key) {
    return key % tableSize;
}

void HashTable::insertItem(Node item) {
    if (currentSize == tableSize) {
        cout << "Hash Table is full, cannot insert\n";
        return;
    }
    int index = hashFunction(item.id);
    int originalIndex = index;
    int i = 0;
    while (table[index].id != -1 && i < tableSize) {
        i++;
        index = (originalIndex + i * i) % tableSize;
    }
    if (table[index].id == -1) {
        table[index] = item;
        currentSize++;
        cout << "Inserted (" << item.id << ", " << item.name << ") at index " << index << endl;
    } else {
        cout << "No empty slot found for (" << item.id << ", " << item.name << ")\n";
    }
}

bool HashTable::searchItem(int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    int i = 0;
    while (table[index].id != -1 && i < tableSize) {
        if (table[index].id == key)
            return true;
        i++;
        index = (originalIndex + i * i) % tableSize;
    }
    return false;
}

void HashTable::displayHash() {
    cout << "\n----- HASH TABLE -----\n";
    for (int i = 0; i < tableSize; i++) {
        cout << i << " --> ";
        if (table[i].id == -1)
            cout << "EMPTY";
        else
            table[i].displayNode();
        cout << endl;
    }
}

[24bcs047@mepcolinux ouadrattic]$cat app.cpp
#include "head.h"

int main() {
    int size, choice, key;
    string name;
    cout << "Enter table size: ";
    cin >> size;
    HashTable ht(size);
    do {
        cout << "\n1.Insert\n2.Search\n3.Display\n4.Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter ID: ";
            cin >> key;
            cout << "Enter Name: ";
            cin >> name;
            ht.insertItem(Node(key, name));
            break;
        case 2:
            cout << "Enter ID to search: ";
            cin >> key;
            if (ht.searchItem(key))
                cout << "Key " << key << " found\n";
            else
                cout << "Key " << key << " not found\n";
            break;
        case 3:
            ht.displayHash();
            break;
        case 4:
            cout << "Exiting\n";
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 4);
    return 0;

}
