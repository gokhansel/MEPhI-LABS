#pragma once

#include "Vertex.h"
#include <chrono>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <random>

using namespace std;

// ребро графа
struct Edge
{
    int first = 0;
    int second = 0;
    double cost = 0.0;

    Edge(int f, int s, double cost) : first(f), second(s), cost(cost){};

    ~Edge() = default;
};


class Graph_ms {
public:
    vector<vector<bool>> mx; // матрица смежности, вершина смежна сама с собой
    vector<Vertex> verts;
    vector<Edge> edges;
    int size_ver = 0;
    int size_edg = 0;

    Graph_ms(const vector<vector<bool>> &matrix, const vector<Vertex> &verts) : mx(matrix), verts(verts), size_ver(verts.size()) {
        for (int i = 0; i < size_ver; ++i)
            for (int j = i + 1; j < size_ver; ++j)
                if (mx[i][j])
                    size_edg++;

        edges.reserve(size_edg);
        for (int i = 0; i < size_ver; ++i)
            for (int j = i + 1; j < size_ver; ++j)
                if (mx[i][j])
                    edges.emplace_back(i, j, dist(verts[i], verts[j]));
    };

    void addVertex(const Vertex &p) {
        for (auto &v: verts)
            if (equal(v, p, 0.001))
                return;

        verts.emplace_back(p);
        for (int i = 0; i < size_ver; ++i)
            mx[i].emplace_back(false);

        mx.emplace_back(vector<bool>(size_ver + 1, false));
        size_ver++;
    }

    void addEdge_vert(const int begin, const int end) {
        if (begin < 0 || begin >= size_ver || end < 0 || end >= size_ver) {
            cerr << "Error in addEdge(" << begin << ", " << end << ")\n";
            throw out_of_range("Error in addEdge");
        }


        if (mx[begin][end])
            return;

        size_edg++;
        edges.emplace_back(Edge(begin, end, dist(verts[begin], verts[end])));
        mx[begin][end] = true;
        mx[end][begin] = true;
    }


    ~Graph_ms() = default;

    vector<double> Ford_Bellman(int start) {
        vector<double> distance(size_ver, 1e9);
        distance[start] = 0.0;
        for (int i = 0; i < size_ver - 1; ++i)
            for (int j = 0; j < size_edg; ++j)
                    distance[edges[j].second] = min(distance[edges[j].second], distance[edges[j].first] + edges[j].cost);

        cout << "Shortest distances (Ford_Bellman):\t\n";
        for (int i = 0; i < size_ver; i++)
            if (distance[i] != 1e9)
                cout << start + 1 << " -> " << i + 1 << " = " << distance[i] << endl;
            else cout << start + 1 << " -> " << i + 1 << " = " << "error" << endl;
        cout << endl;
        return distance;
    }


    vector<double> Ford_Bellman_new(int start) {
        vector<double> distance(size_ver, 1e9);
        distance[start] = 0.0;
        for (int i = 0; i < size_ver - 1; ++i) {
            bool any = false;
            for (int j = 0; j < size_edg; ++j)
                if (distance[edges[j].first] < 1e9)
                    if (distance[edges[j].second] > distance[edges[j].first] + edges[j].cost) {
                        distance[edges[j].second] = distance[edges[j].first] + edges[j].cost;
                        any = true;
                    }
            if (!any) break;
        }

        cout << "Shortest distances (Ford_Bellman_new):\t\n";
        for (int i = 0; i <size_ver; i++)
            if (distance[i] != 1e9)
                cout << start + 1 << " -> " << i + 1 << " = " << distance[i] << endl;
            else cout << start + 1 << " -> " << i + 1 << " = " << "error" << endl;
        cout << endl;
        return distance;
    }
};

// Генерация случайного графа заданного размера
Graph_ms generateGraph(int n)
{

    vector<vector<bool>> mx(n);
    random_device rd;
    mt19937 mersenne(rd());
    for (int i = 0; i < n; i++)
    {
        mx[i].resize(n, false);
        for (int j = 0; j < n; j++)
            if (mersenne() % (n / 3) == 3)
                mx[i][j] = true;
        mx[i][i] = true;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
            if (mx[j][i])
                mx[i][j] = true;
    }

    vector<Vertex> verts(n);
    for (int i = 0; i < n; i++)
        verts[i] = Vertex(mersenne() % 3 * n, mersenne() % 3 * n, 0);

    Graph_ms graph(mx, verts);
    return graph;
}
