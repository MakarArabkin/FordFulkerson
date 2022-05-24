#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <limits.h>
#include <list>
#include <queue>
#include<algorithm>

using namespace std;

class Graph {
    vector<vector<int>> adjMatrix;
    vector<string> split(const string& str, char delim) {
        vector<string> result;
        istringstream iss(str);
        string item;
        while (getline(iss, item, delim))
            result.push_back(item);
        return result;
    }
    vector<string> vertexTable;

public:
    int getNumOfVertices() { return vertexTable.size(); }

    string getVertexById(int id) {
        return vertexTable.at(id);
    }

    int getVertexId(string vertex) {
        for (int i = 0; i < vertexTable.size(); i++) {
            if (vertexTable.at(i) == vertex)
                return i;
        }
        return -1;
    }

    int getWeight(int vFrom, int vTo) { return adjMatrix[vFrom][vTo]; }

    void setWeight(int vFrom, int vTo, int weight) { adjMatrix[vFrom][vTo] = weight; }

    Graph(string data);

    Graph(Graph& graph) {
        for (int i = 0; i < graph.getNumOfVertices(); i++) {
            vertexTable.push_back(graph.getVertexById(i));
        }
        int n = getNumOfVertices();
        for (int i = 0; i < n; i++) {
            vector<int> vertices;
            for (int j = 0; j < n; j++) {
                vertices.push_back(0);
            } 
            adjMatrix.push_back(vertices);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adjMatrix[i][j] = graph.getWeight(i, j);
            }
        }
    }

    void updateNet(int s, int t, int flow, vector<int> path) {
        for (int v = t; v != s; v = path[v]) {
            int u = path[v];
            setWeight(u, v, getWeight(u, v) - flow);
            setWeight(v, u, getWeight(v, u) + flow);
        }
    }

    int findFlowByPath(int s, int t, vector<int> path) {
        int flow = INT_MAX;
        for (int v = t; v != s; v = path[v]) {
            int u = path[v];
            flow = min(flow, getWeight(u, v));
        }
        return flow;
    }
};

Graph::Graph(string data) {
    vector<string> rates = split(data, '\n');

    for (string& rate : rates) {
        vector<string> words = split(rate, ' ');
        if (find(vertexTable.begin(), vertexTable.end(), words.at(0)) == vertexTable.end()) {
            vertexTable.push_back(words.at(0));
        }
        if (find(vertexTable.begin(), vertexTable.end(), words.at(1)) == vertexTable.end()) {
            vertexTable.push_back(words.at(1));
        }
    }
    
    for (int i = 0; i != vertexTable.size(); i++) {
        vector<int> vertices;
        for (int j = 0; j != vertexTable.size(); j++) {
            vertices.push_back(0);
        }
        adjMatrix.push_back(vertices);
    }
            
    for (string& rate : rates)
    {
        vector<string> words = split(rate, ' ');
        int vFrom = getVertexId(words.at(0));
        int vTo = getVertexId(words.at(1));
        int weight = stoi(words.at(2));
        adjMatrix[vFrom][vTo] = weight;
    }
}

string readData(string path) {
    string data = "";
    string line;
    ifstream file(path);
    if (file.is_open())
        while (getline(file, line))
            data += line + "\n";
    file.close();
    return data;
}

bool isThereFlow(Graph graph, int s, int t, vector<int>& path)
{
    int n = graph.getNumOfVertices();
    vector<int> visited;
    queue<int> q;
    q.push(s);
    visited.push_back(s);
    if (path.size() != n)
        for (int i = 0; i < n; i++) path.push_back(-2);
    path[s] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            if (find(visited.begin(), visited.end(), v) == visited.end() && graph.getWeight(u, v) > 0) {
                if (v == t) {
                    path[v] = u;
                    return true;
                }
                q.push(v);
                path[v] = u;
                visited.push_back(v);
            }
        }
    }
    return false;
}

int fordFulkerson(Graph graph, string src, string snk)
{
    int s = graph.getVertexId(src);
    int t = graph.getVertexId(snk);
    int n = graph.getNumOfVertices();
    Graph rGraph(graph);
    vector<int> path;
    int maxFlow = 0; 

    while (isThereFlow(rGraph, s, t, path)) {
        int flow = rGraph.findFlowByPath(s, t, path);
        rGraph.updateNet(s, t, flow, path);
        maxFlow += flow;
    }
      
    return maxFlow;
}

int main()
{
    string data = readData("Data.txt");
    Graph graph(data);
    int maxFlow = fordFulkerson(graph, "S", "T");
    cout << maxFlow;
}

