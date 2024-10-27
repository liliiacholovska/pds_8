#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

const int MAX_VERTICES = 100;
const int MAX_EDGES = 100;

int adjList[MAX_VERTICES][MAX_EDGES];
int edgeCount[MAX_VERTICES];
bool visited[MAX_VERTICES];
int dfsNumber[MAX_VERTICES];

void initializeGraph() {
    for (int i = 0; i < MAX_VERTICES; ++i) {
        edgeCount[i] = 0;
        visited[i] = false;
        dfsNumber[i] = 0;
    }
}

void addEdge(int u, int v) {
    adjList[u][edgeCount[u]++] = v;
    adjList[v][edgeCount[v]++] = u;
}

void loadGraphFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Помилка відкриття файлу." << endl;
        return;
    }

    int u, v;
    while (file >> u >> v) {
        addEdge(u, v);
    }
    file.close();
}

void DFS(int start) {
    int stack[MAX_VERTICES];
    int top = -1;
    int counter = 0;

    stack[++top] = start;

    cout << "Поточна вершина\tDFS Номер\tВміст стеку" << endl;
    cout << "--------------------------------------------------" << endl;

    while (top >= 0) {
        int current = stack[top];

        if (!visited[current]) {
            visited[current] = true;
            dfsNumber[current] = ++counter;
            cout << current << "\t\t" << dfsNumber[current] << "\t\t";

            for (int i = 0; i <= top; ++i) {
                cout << stack[i] << " ";
            }
            cout << endl;
        }

        bool hasUnvisitedNeighbors = false;
        for (int i = edgeCount[current] - 1; i >= 0; --i) {
            int neighbor = adjList[current][i];
            if (!visited[neighbor]) {
                stack[++top] = neighbor;
                hasUnvisitedNeighbors = true;
                break;
            }
        }

        if (!hasUnvisitedNeighbors) {
            --top;
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    initializeGraph();

    string filename;
    int startVertex;

    cout << "Введіть назву файлу: ";
    cin >> filename;
    loadGraphFromFile(filename);

    cout << "Введіть початкову вершину: ";
    cin >> startVertex;

    DFS(startVertex);

    return 0;
}