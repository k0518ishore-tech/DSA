#include <iostream>
#include<string.h>
class node{
    private:
      int vid;
      char vname[50];
    public:
      node();
      void displayDetails();
      void getDetails();
    friend class linearProbing;
};
using namespace std;
class LinearProbing
{
    private:
    int tablesize;
    int *HT;
    public:
    LinearProbing(int);
    ~LinearProbing();
    int hashFunction(int,int);
    int insert(int);
    int delete1(int);
    int search(int);
    void display();
};
[24bcs047@mepcolinux linear]$cat imp1.cpp
#include "head1.h"
node :: node (){
   vid=-1;
   strcpy(vname," ");
}
void node :: getDetails(){
   cout<<"Enter COC Power (ID):";
   cin>>vid;
   cout<<"Enter COC name :";
   cin>>vname;
}
void node :: displayDetails(){
   cout<<"Power :"<<vid<<"\t";
   cout<<" COC Name :"<<vname;
}


LinearProbing::LinearProbing(int s)
{
    tablesize=s;
    HT=new node*[s];
    isDeleted = new bool[s];
    for(int i=0;i<tablesize;i++)
    {
        HT[i]=NULL;
        isDeleted[i] = false;
    }
}

LinearProbing::~LinearProbing()
{

    for(int i=0; i<tablesize; ++i) {
        if(HT[i] != NULL) {
            delete HT[i];
        }
    }
    delete[] HT;
    delete[] isDeleted;
    tablesize=0;
}


int LinearProbing::hashFunction(int key)
{
    return key % tablesize;
}


int LinearProbing::insert(node* newNode)
{
    int startIdx = hashFunction(newNode->vid);
    int index = startIdx;

    do {

        if (HT[index] == NULL || isDeleted[index]) {
            if (HT[index] == NULL) {

                HT[index] = new node();
            }

            HT[index]->vid = newNode->vid;
            strcpy(HT[index]->vname, newNode->vname);
            isDeleted[index] = false;
            delete newNode;
            return index;
        }


        if (HT[index]->vid == newNode->vid && !isDeleted[index]) {
             cout << "Error: ID " << newNode->vid << " already exists." << endl;
             delete newNode;
             return -1;
        }

        index = (index + 1) % tablesize;
    } while (index != startIdx);

    delete newNode;
    return -2;
}

int LinearProbing::delete1(int key)
{
    int startIdx = hashFunction(key);
    int index = startIdx;

    do {
        if (HT[index] != NULL && !isDeleted[index] && HT[index]->vid == key) {
            isDeleted[index] = true;
            return index;
        }


        if (HT[index] == NULL) {
            return -2;
        }

        index = (index + 1) % tablesize;
    } while (index != startIdx);

    return -2;
}

int LinearProbing::search(int key)
{
    int startIdx = hashFunction(key);
    int index = startIdx;

    do {
        if (HT[index] != NULL && !isDeleted[index] && HT[index]->vid == key) {
            return index;
        }

        if (HT[index] == NULL) {
            return -2;
        }

        index = (index + 1) % tablesize;
    } while (index != startIdx);

    return -2;
}

void LinearProbing::display()
{
    for(int i=0;i<tablesize;i++)
    {
        cout<<"Index "<<i<<": ";
        if(HT[i]==NULL)
        {
            cout<<"Empty"<<endl;
        }
        else if (isDeleted[i]) {
            cout << "[DELETED]" << endl;
        }
        else
        {
            HT[i]->displayDetails();
            cout << endl;
        }
    }
}
[24bcs047@mepcolinux linear]$cat app.cpp
#include "head.h"
int main()
{
    int s;
    cout<<"Enter the table size:"<<endl;
    cin>>s;
    LinearProbing ob1(s);
    int ch;
    cout<<"1.Insert\n2.Delete\n3.Search\n4.Display\n5.Exit\n";
    do{
        cout<<"Enter the choice:"<<endl;
        cin>>ch;
        switch(ch)
        {
            case 1:
            {
                int k;
                cout<<"Enter the element to insert:";
                cin>>k;
                int out=ob1.insert(k);
                if(out==-2)
                {
                    cout<<"The table is full insertion fails"<<endl;
                }
                else
                {
                    cout<<"The element is inserted at  "<<out<<endl;
                }
                break;
            }
            case 2:
            {
                int k;
                cout<<"Enter the key to delete:";
                cin>>k;
                int out=ob1.delete1(k);
                if(out==-2)
                {
                    cout<<"The key is not present in the table deletion fails"<<endl;
                }
                else
                {
                    cout<<"The element is deleted at  "<<out<<endl;
                }
                break;
            }
            case 3:
            {
                int k;
                cout<<"Enter the key to search:";
                cin>>k;
                int out=ob1.search(k);
                if(out==-2)
                {
                    cout<<"The key is not found in the table"<<endl;
                }
                else
                {
                    cout<<"The key is present in the table at  "<<out<<endl;
                }
                break;
            }
            case 4:
            {
                cout<<"The table is"<<endl;
                ob1.display();
                break;
            }
            default:
            cout<<"Invalid Expression\n";
        }
    }while(ch!=5);
    cout<<"Exiting the program"<<endl;

}