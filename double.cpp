#include <iostream>
#include <string>
using namespace std;
class Node
{
public:
    int id;
    string name;

public:
    Node();
    void getDetails();
    void displayDetails();
};

class HashTable
{
    Node *table;
    int tableSize, currentSize, prime;
    bool custom;
    int a1, b1, a2, b2;

public:
    HashTable(int size);
    HashTable(int size, int p1, int q1, int p2, int q2);
    ~HashTable();
    bool isPrime(int num);
    int findPrime(int num);
    int hash1(int key);
    int hash2(int key);
    void insertItem(Node n);
    bool searchItem(int key);
    void displayHash();
};



[24bcs047@mepcolinux double]$cat imp.cpp
#include"head.h"


Node::Node()
{
    id = -1;
    name = "";
}

void Node::getDetails()
{
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin >> name;
}

void Node::displayDetails() { cout << id << " (" << name << ")"; }

HashTable::HashTable(int size)
{
    tableSize = size;
    currentSize = 0;
    custom = false;
    table = new Node[tableSize];
    prime = findPrime(tableSize);
}

HashTable::HashTable(int size, int p1, int q1, int p2, int q2)
{
    tableSize = size;
    currentSize = 0;
    custom = true;
    a1 = p1;
    b1 = q1;
    a2 = p2;
    b2 = q2;
    table = new Node[tableSize];
    prime = findPrime(tableSize);
}

HashTable::~HashTable() { delete[] table; }

bool HashTable::isPrime(int num)
{
    if (num <= 1)
        return false;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return false;
    return true;
}

int HashTable::findPrime(int num)
{
    for (int i = num - 1; i >= 2; i--)
        if (isPrime(i))
            return i;
    return 3;
}

int HashTable::hash1(int key)
{
    if (custom)
        return ((a1 * key) + b1) % tableSize;
    return key % tableSize;
}

int HashTable::hash2(int key)
{
    if (custom)
    {
        // Added modulo operation to ensure a non-negative result before final subtraction
        int h = prime - ((((a2 * key) + b2) % prime + prime) % prime);
        if (h == 0)
            h = 1;
        return h;
    }
    // Added modulo operation to handle potential negative results
    return prime - ((key % prime + prime) % prime);
}

void HashTable::insertItem(Node n)
{
    if (currentSize == tableSize)
    {
        cout << "Table full\n";
        return;
    }
    int index1 = hash1(n.id), step = hash2(n.id), index = index1;
    cout << "Inserting ";
    n.displayDetails();
    cout << " | h1=" << index1 << ", h2=" << step << endl;
    if (table[index].id == -1)
    {
        table[index] = n;
        currentSize++;
        cout << "Inserted at " << index << endl;
        return;
    }
    for (int i = 1; i < tableSize; i++)
    {
        int newIndex = (index1 + i * step) % tableSize;
        if (table[newIndex].id == -1)
        {
            table[newIndex] = n;
            currentSize++;
            cout << "Inserted at " << newIndex << endl;
            return;
        }
    }
    cout << "No slot for ID " << n.id << endl;
}

bool HashTable::searchItem(int key)
{
    int index1 = hash1(key), step = hash2(key);
    if (table[index1].id == key)
        return true;
    for (int i = 1; i < tableSize; i++)
    {
        int newIndex = (index1 + i * step) % tableSize;
        if (table[newIndex].id == key)
            return true;
        if (table[newIndex].id == -1)
            break;
    }
    return false;
}

void HashTable::displayHash()
{
    cout << "\nHash Table:\n";
    for (int i = 0; i < tableSize; i++)
    {
        cout << i << " -> ";
        if (table[i].id == -1)
            cout << "EMPTY";
        else
            table[i].displayDetails();
        cout << endl;
    }
}

[24bcs047@mepcolinux double]$cat app.cpp
#include"head.h"



int main()
{
    int size, mode;
    cout << "Enter table size: ";
    cin >> size;
    cout << "Enter 0 for default or 1 for custom hash: ";
    cin >> mode;

    HashTable *ht;
    if (mode == 0)
        ht = new HashTable(size);
    else
    {
        int a1, b1, a2, b2;
        cout << "Enter a1, b1 for h1(x)=a1*x+b1: ";
        cin >> a1 >> b1;
        cout << "Enter a2, b2 for h2(x)=a2*x+b2: ";
        cin >> a2 >> b2;
        ht = new HashTable(size, a1, b1, a2, b2);
    }

    int choice, key;
    do
    {
        cout << "\n1.Insert\n2.Search\n3.Display\n4.Exit\nChoice: ";
        cin >> choice;
        if (choice == 1)
        {
            Node n;
            n.getDetails();
            ht->insertItem(n);
        }
        else if (choice == 2)
        {
            cout << "Enter ID to search: ";
            cin >> key;
            if (ht->searchItem(key))
                cout << "Record found\n";
            else
                cout << "Record not found\n";
        }
        else if (choice == 3)
            ht->displayHash();
        else if (choice == 4)
            cout << "Exiting...\n";
        else
            cout << "Invalid choice\n";
    } while (choice != 4);

    delete ht;
    return 0;
}