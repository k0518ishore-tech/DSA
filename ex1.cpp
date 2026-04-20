#include <iostream>

using namespace std;

class A_List {
private:
    int *arr;
    int Size;
    int capacity;

public:
    A_List();
    A_List(int *, int, int);
    A_List(const A_List&);
    void display() ;
    void makeListEmpty();
    int isFull();
    int isEmpty();
    int insertAtFirst(int);
    int insertAtLast(int);
    int insertByPos(int,int);
    int deleteAtFirst();
    int deleteAtLast();
    int deleteByPos(int);
    int searchAtFirst();
    int searchAtLast();
    int searchAnElement(int);
    int retriveEltAtIndex(int);
};
[24bcs047@mepcolinux ex1]$cat im.cpp
#include"head.h"
A_List::A_List() {
    Size = 0;
    capacity = 0;
    arr = new int[capacity];
    for (int i =0 ;i<capacity; i++)
        arr[i]=-1;
}

A_List::A_List(int *a, int c, int s) {
    capacity = c;
    Size = s;
    arr = new int[capacity];

    for (int i = 0; i < Size; i++)
        arr[i] = a[i];
    for (int i = Size; i < capacity; i++)
        arr[i] = -1;
}

A_List::A_List(const A_List& other) {
    Size = other.Size;
    capacity = other.capacity;
    arr = new int[capacity];
    for (int i = 0; i < Size; i++)
        arr[i] = other.arr[i];
    for (int i = Size; i < capacity; i++)
        arr[i] = -1;
}

void A_List::display()  {
    for (int i = 0; i < Size; i++)
          cout << arr[i] << " ";
    cout << endl;
}

int A_List::isFull() {
    return Size==capacity;
}

int A_List::isEmpty() {
    return Size==0;
}

int A_List::insertAtLast(int element) {
    if (!isFull()) {
        arr[Size++]=element;
        return 1;
    }
    else
        return -1;
}

int A_List::insertAtFirst(int element) {
    if (!isFull()) {
        if (isEmpty())
            arr[Size++]=element;
        else {
            for(int i = Size; i > 0; i--)
                arr[i]=arr[i-1];
            arr[0]=element;
            Size++;
        }
        return 1;
    }
    else
        return 0;
}

int A_List::insertByPos(int pos, int element) {
    if (!isFull()) {
        if (pos <= 0 || pos > Size+1)
            return -2;
        if(pos == 1)
            return insertAtFirst(element);
        else {
            for (int i = Size; i >= pos; i--)
                arr[i] = arr[i-1];
            arr[pos-1] = element;
            Size++;
            return 1;
        }
    }
    else
        return 0;
}

int A_List::deleteAtFirst() {
    if(!isEmpty()) {
        for(int i = 0; i < Size-1; i++)
            arr[i] = arr[i+1];
        Size--;
        return 1;
    }
    else
        return -1;
}

int A_List::deleteAtLast() {
    if (!isEmpty()) {
        arr[--Size]=-1;
        return 1;
    }
    else
        return -1;
}

int A_List::deleteByPos(int pos) {
    if(!isEmpty()) {
        if (pos <= 0 || pos > Size)
            return -2;
        for (int i = pos-1; i < Size-1; i++)
            arr[i] = arr[i+1];
        Size--;
        return 1;
    }
    else
        return -1;
}

int A_List::searchAtFirst() {
    if(!isEmpty())
        return arr[0];
    else
        return -1;
}

int A_List::searchAtLast() {
    if(!isEmpty())
        return arr[Size-1];
    else
        return -1;
}

int A_List::searchAnElement(int element){
    if(!isEmpty()){
        for(int i = 0; i < Size; i++){
            if(arr[i] == element){
                return i;
            }
        }
        return -2;
    }
    else
        return -1;
}

int A_List::retriveEltAtIndex(int index){
    if (!isEmpty()){
        if(index >= 0 && index < Size){
            return arr[index];
        }
        else
            return -2;
    }
    else
        return -1;
}

void A_List::makeListEmpty(){
    while(!isEmpty())
        deleteAtFirst();
}
[24bcs047@mepcolinux ex1]$cat ap.cpp
#include"head.h"
int main()
{
    int my_capacity, my_size;
    cout << "Enter capacity: ";
    cin >> my_capacity;
    cout << "Enter size: ";
    cin >> my_size;

    int* data_arr = new int[my_capacity];

    for (int i = 0; i < my_size; i++) {
        cout << "enter element " << i+1 << ": ";
        cin >> data_arr[i];
    }

    A_List obj(data_arr, my_capacity, my_size);
    int choice, value, pos, result;
    cout<< "\n Menu\n";
    cout<< "1. Insert at First \n2. Insert at Last \n3. Insert by Position\n";
    cout<< "4. Delete at First \n5. Delete at Last \n6. Delete by Position\n";
    cout<< "7. Search at First \n8. Search at Last \n9. Search an Element \n10. Retrieve Element at Index \n";
    cout<< "11. Display List \n12. Check if Full \n13. Check if Empty\n";
    cout<< "14. Make List Empty \n0. Exit\n ";

    do {
        //cout<< "\n Menu\n";
        //cout<< "1. Insert at First \n2. Insert at Last \n3. Insert by Position\n";
        //cout<< "4. Delete at First \n5. Delete at Last \n6. Delete by Position\n";
        //cout<< "7. Search at First \n8. Search at Last \n9. Search an Element \n10. Retrieve Element at Index \n";
        //cout<<"11. Display List \n12. Check if Full \n13. Check if Empty\n";
        //cout<<"14. Make List Empty \n0. Exit\n Enter your choice: ";
        cout<<"Enter your choice : ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                result = obj.insertAtFirst(value);
                cout << (result == 1 ? "Success" : "Failed") << endl;
                break;

            case 2:
                cout << "Enter value: ";
                cin >> value;
                result = obj.insertAtLast(value);
                cout << (result == 1 ? "Success" : "Failed") << endl;
                break;

            case 3:
                cout << "Enter value and position: ";
                cin >> value >> pos;
                result = obj.insertByPos(pos, value);  // Fixed parameter order
                if(result == 1) cout << "Success" << endl;
                else if(result == -2) cout << "Invalid position" << endl;
                else if(result == 0) cout << "List is full" << endl;
                break;

            case 4:
                result = obj.deleteAtFirst();
                cout << (result == 1 ? "Success" : "Failed") << endl;
                break;

            case 5:
                result = obj.deleteAtLast();
                cout << (result == 1 ? "Success" : "Failed") << endl;
                break;

            case 6:
                cout << "Enter position: ";
                cin >> pos;
                result = obj.deleteByPos(pos);
                if(result == 1) cout << "Success" << endl;
                else if(result == -2) cout << "Invalid position" << endl;
                else cout << "List is empty" << endl;
                break;

            case 7:
                result = obj.searchAtFirst();
                if(result != -1) cout << "Element found: " << result << endl;
                else cout << "List is empty" << endl;
                break;

            case 8:
                result = obj.searchAtLast();
                if(result != -1) cout << "Element found: " << result << endl;
                else cout << "List is empty" << endl;
                break;

            case 9:
                cout << "Enter element to search: ";
                cin >> value;
                result = obj.searchAnElement(value);
                if(result >= 0) cout << "Element found at index: " << result << endl;
                else if(result == -2) cout << "Element not found" << endl;
                else cout << "List is empty" << endl;
                break;

            case 10:
                cout << "Enter index: ";
                cin >> pos;
                result = obj.retriveEltAtIndex(pos);
                if (result != -1 && result != -2)
                    cout << "Element at index " << pos << " is: " << result << endl;
                else if(result == -2)
                    cout << "Invalid index" << endl;
                else
                    cout << "List is empty" << endl;
                break;

            case 11:
                obj.display();
                break;

            case 12:
                result = obj.isFull();
                cout << (result ? "List is full" : "List is not full") << endl;
                break;

            case 13:
                result = obj.isEmpty();
                cout << (result ? "List is empty" : "List is not empty") << endl;
                break;

            case 14:
                obj.makeListEmpty();
                cout << "List has been made empty." << endl;
                break;

            case 0:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 0);

    delete[] data_arr;
    return 0;
}
