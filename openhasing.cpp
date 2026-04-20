#include <iostream>
using namespace std;
class H_Node{
    private:
      int data;
      H_Node* next;
    public:
      H_Node(int data);
      ~H_Node();
    friend class O_Hash;
};
class O_Hash{
    private:
      int size;
      H_Node** arr;
    public:
      O_Hash(int);
      ~O_Hash();
      int insert(int);
      int delete1(int);
      int search(int);
      void display();
      int hashFunction(int);
};

[24bcs047@mepcolinux ex9]$cat imp.cpp
#include"head1.h"
H_Node::H_Node(int data1, string vname1)
{
    data = data1;
    vname = vname1;
    next = NULL;
}

H_Node::~H_Node()
{
}


O_Hash::O_Hash(int s)
{
    size = s;
    arr = new H_Node*[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = NULL;
    }
}

O_Hash::~O_Hash()
{

    for (int i = 0; i < size; ++i) {
        H_Node* current = arr[i];
        while (current != NULL) {
            H_Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] arr;
}

int O_Hash::hashFunction(int key)
{
    return key % size;
}


int O_Hash::insert(int key, string name)
{
    int index = hashFunction(key);
    H_Node* newNode = new H_Node(key, name);
    newNode->next = arr[index];
    arr[index] = newNode;
    return index;
}

int O_Hash::delete1(int key)
{
    int index = hashFunction(key);
    H_Node* temp = arr[index];
    H_Node* prev = NULL;
    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        return -1;
    }
    if (prev == NULL)
    {
        arr[index] = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }
    delete temp;
    return 1;
}

void O_Hash::display()
{

    for (int i = 0; i < size; i++)
    {
        H_Node* temp = arr[i];
        cout << "Bucket " << i << ": ";
        if (temp == NULL)
        {
            cout << "Empty";
        }
        else
        {
            while (temp != NULL)
            {

                cout << temp->data << "|" << temp->vname;
                if (temp->next != NULL) {
                    cout << "\t-> ";
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }
    cout << endl;
}

int O_Hash::search(int key)
{
    int index = hashFunction(key);
    H_Node* temp = arr[index];
    while (temp != NULL)
    {
        if (temp->data == key)
        {
            return index;
        }
        temp = temp->next;
    }
    return -1;
}

[24bcs047@mepcolinux ex9]$cat app.cpp
#include "head1.h"
int main()
{
    int s;
    cout << "Enter the table size:";
    cin >> s;
    O_Hash ob1(s);
    int ch;
    cout << "1.Insert\n2.Delete\n3.Display\n4.Search\n5.Exit\n";
    do {
        cout << "Enter the choice:" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
        {
            int k;
            string name;
            cout << "Enter no the Elixer :";
            cin >> k;
            cout << "Enter Troop name:";
            cin >> name;
            int out = ob1.insert(k, name);
            cout << "The element is inserted at " << out << " bucket" << endl;
            break;
        }
        case 2:
        {
            int k;
            cout << "Enter the element to delete:";
            cin >> k;
            int out = ob1.delete1(k);
            if (out == -1)
            {
                cout << "The element is not found in the table" << endl;
            }
            else
            {
                cout << "The element is deleted successfully" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "Table:" << endl;
            ob1.display();
            break;
        }
        case 4:
        {
            int k;
            cout << "Enter the key to search:";
            cin >> k;
            int out = ob1.search(k);
            if (out == -1)
            {
                cout << "The key is not present in the table" << endl;
            }
            else
            {
                cout << "The key is present in the table at " << out << endl;
            }
            break;
        }
        case 5:
        {
            break;
        }
        default:
            cout << "Invalid Expression\n";
        }
    } while (ch != 5);
    cout << "Exiting the program" << endl;
    return 0;
}
