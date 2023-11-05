#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"

using namespace std;


int shortestPath(vector<vector<int>> graph, int start, int finish) {
    size_t n = graph.size();
    vector<int> distance(n, INT_MAX);
    Queue* que = queue_create();

    distance[start] = 0;
    queue_insert(que,(Data)start);

    while (!queue_empty(que)) {
        Data i = queue_get(que);
        queue_remove(que);

        for (size_t j = 0; j < n; ++j) {
            if (graph[i][j] != 0 && distance[j] == INT_MAX) {
                distance[j] = distance[i] + 1;
                if (queue_empty(que)) {
                    que = queue_create();
                }
                queue_insert(que, (Data)j);
            }
        }
    }

    if (distance[finish] == INT_MAX) {
        return -1;
    }
    return distance[finish];
}

int main() {
    ifstream input("input.txt");
    

    int n, start, finish;
    input >> n >> start >> finish;

    vector<vector<int>> graph;

    for (int i = 0; i < n; ++i) {
        graph.push_back({});
        for (int j = 0; j < n; ++j) {
            int num;
            input >> num;
            graph[i].push_back(num);
        }
    }
    input.close();

    int result = shortestPath(graph, start - 1, finish - 1);

    ofstream output("output.txt");

    if (result == -1) {
        output << "IMPOSSIBLE";
    }
    else {
        output << result;
    }

    output.close();
}