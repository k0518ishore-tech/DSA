#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    int id;
    string name;
    Node();
    void getDetails();
    void displayDetails();
};

class Queue {
    Node* queuearr;
    int capacity;
    int front;
    int rear;
public:
    Queue(int );
    ~Queue();
    int enqueue(Node);
    Node dequeue();
    int isFull();
    int isEmpty();
};

class Graph {
    int V;
    Node* nodes;
    int** adj;

public:
    Graph(int vertices, Node* n, int** matrix);
    ~Graph();
    void BFS(int startID);
    void DFS(int startID);
    void DFSRecursive(int node, bool visited[]);

};

[24bcs047@mepcolinux ex8]$cat imp.cpp
#include"head.h"
Node::Node() {
    id = -1;
    name = "";
}
void Node::getDetails() {
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin >> name;
}
void Node::displayDetails() {
    cout << id << "(" << name << ") ";
}
Queue::Queue(int c) {
    capacity = c;
    front = -1;
    rear = -1;
    queuearr = new Node[capacity];
}
Queue::~Queue() {
    delete[] queuearr;
}
int Queue::isEmpty() {
    return (front == -1 && rear == -1) || (front > rear);
}

int Queue::isFull() {
    return ((rear + 1) == capacity);
}
int Queue::enqueue(Node element) {
    if(!isFull()) {
        if(front == -1 && rear == -1) {
            front = 0;
            rear = 0;
            queuearr[rear] = element;
        }
        else {
            queuearr[++rear] = element;
        }
        return 1;
    }
    else {
        return -1;
    }
}

Node Queue::dequeue() {
    Node emptyNode;
    emptyNode.id = -1;
    if(!isEmpty()) {
        Node dltelt = queuearr[front];
        if(front == rear) {
            front = -1;
            rear = -1;
        }
        else {
            front++;
        }
        return dltelt;
    }
    else {
        return emptyNode;
    }
}
Graph::Graph(int vertices, Node* n, int** matrix) {
    V = vertices;
    nodes = new Node[V];
    for(int i = 0; i < V; i++) {
        nodes[i] = n[i];
    }
    adj = new int*[V];
    for(int i = 0; i < V; i++) {
        adj[i] = new int[V];
        for(int j = 0; j < V; j++) {
            adj[i][j] = matrix[i][j];
        }
    }
}
Graph::~Graph() {
    delete[] nodes;
    for(int i = 0; i < V; i++) {
        delete[] adj[i];
    }
    delete[] adj;
}
void Graph::BFS(int startID) {
    bool* visited = new bool[V];
    for(int i = 0; i < V; i++) {
        visited[i] = false;
    }
    Queue q(V);
    q.enqueue(nodes[startID]);
    visited[startID] = true;
    cout << "BFS Traversal: ";
    while(!q.isEmpty()) {
        Node curr = q.dequeue();
        if(curr.id != -1) {
            curr.displayDetails();
            int idx = curr.id;
            for(int j = 0; j < V; j++) {
                if(adj[idx][j] == 1 && !visited[j]) {
                    q.enqueue(nodes[j]);
                    visited[j] = true;
                }
            }
        }
    }
    cout << endl;
    delete[] visited;
}
void Graph::DFS(int startID) {
    bool* visited = new bool[V];
    for(int i = 0; i < V; i++) {
        visited[i] = false;
    }
    cout << "DFS Traversal: ";
    DFSRecursive(startID, visited);
    cout << endl;
    delete[] visited;
}
void Graph::DFSRecursive(int node, bool visited[]) {
    visited[node] = true;
    nodes[node].displayDetails();
    for(int i = 0; i < V; i++) {
        if(adj[node][i] == 1 && !visited[i]) {
            DFSRecursive(i, visited);
        }
    }
}
#include"head.h"
int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;
    Node* nodes = new Node[V];
    for(int i = 0; i < V; i++) 
        cout << "Enter details for node " << i + 1 << ":\n";
        nodes[i].getDetails();
    }
    int** matrix = new int*[V];
    for(int i = 0; i < V; i++) {
        matrix[i] = new int[V];
        cout << "Enter adjacency for node " << nodes[i].id << " (0/1 for each vertex): ";
        for(int j = 0; j < V; j++) {
            cin >> matrix[i][j];
        }
    }
    Graph g(V, nodes, matrix);
    int choice, start;
    do {
        cout << "\n1. BFS\n2. DFS c\n3. Exit\nEnter choice: ";
        cin >> choice;
        if(choice == 1) {
            cout << "Enter start node id: ";
            cin >> start;
            g.BFS(start);
        }
        else if(choice == 2) {
            cout << "Enter start node id: ";
            cin >> start;
            g.DFS(start);
        }
    } while(choice != 3);
    for(int i = 0; i < V; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] nodes;
    return 0;
}
