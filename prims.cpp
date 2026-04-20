#include <iostream>
#include <string>
using namespace std;

class Node
{
    int id;
    string name;

public:
    Node();
    void getDetails();
    int getId();
    string getName();
};

class Graph
{
    int V;
    Node *nodes;
    int **graph;

public:
    Graph(int vertices, Node *n, int **matrix);
    ~Graph();
    int minKey(int key[], bool mstSet[]);

    void primMST();
};

[24bcs047@mepcolinux ex11]$cat imp.cpp
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
int Node::getId() { return id; }
string Node::getName() { return name; }

Graph::Graph(int vertices, Node *n, int **matrix)
{
    V = vertices;
    nodes = n;
    graph = new int *[V];
    for (int i = 0; i < V; i++)
    {
        graph[i] = new int[V];
        for (int j = 0; j < V; j++)
            graph[i][j] = matrix[i][j];
    }
}

Graph::~Graph()
{
    for (int i = 0; i < V; i++)
        delete[] graph[i];
    delete[] graph;
}

int Graph::minKey(int key[], bool mstSet[])
{
    int min = 9999, min_index = -1;
    for (int v = 0; v < V; v++)
        if (!mstSet[v] && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void Graph::primMST()
{
    int *parent = new int[V];
    int *key = new int[V];
    bool *mstSet = new bool[V];

    for (int i = 0; i < V; i++)
        key[i] = 9999, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
    }

    cout << "\nMinimum Spanning Tree:\n";
    cout << "Edge\t\tWeight\n";
    int totalWeight = 0;
    for (int i = 1; i < V; i++)
    {
        cout << nodes[parent[i]].getName() << " - " << nodes[i].getName() << "\t" << graph[i][parent[i]] << endl;
        totalWeight += graph[i][parent[i]];
    }
    cout << "\nTotal Weight of MST = " << totalWeight << endl;

    delete[] parent;
    delete[] key;
    delete[] mstSet;
}

[24bcs047@mepcolinux ex11]$cat app.cpp
#include"head.h"
int main()
{
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    Node *nodes = new Node[V];
    for (int i = 0; i < V; i++)
    {
        cout << "\nEnter details for node " << i + 1 << ":\n";
        nodes[i].getDetails();
    }

    int **matrix = new int *[V];
    for (int i = 0; i < V; i++)
    {
        matrix[i] = new int[V];
        cout << "\nEnter adjacency matrix row for vertex " << nodes[i].getName() << " (use 0 if no edge, weight if connected):\n";
        for (int j = 0; j < V; j++)
        {
            cin >> matrix[i][j];
        }
    }

    Graph g(V, nodes, matrix);
    g.primMST();

    for (int i = 0; i < V; i++)
        delete[] matrix[i];
    delete[] matrix;
    delete[] nodes;
    return 0;
}