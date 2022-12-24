#pragma once

#include <chrono>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <random>
#include <iostream>

using namespace std;

// Неориентированный граф (матрица смежности с учетом веса ребра)
class Graph_mr {
public:
    vector <vector<int>>  mx;
    int size_ver;
    int size_adg = 0;

    explicit Graph_mr(const vector<vector<int>> &matrix) : mx(matrix), size_ver(int(mx.size())){
        for (int i = 0; i < size_ver; ++i)
            for (int j = i + 1; j < size_ver; ++j) {
                if (mx[i][j])
                    size_adg++;
            }
    }

    void addEdge_vert(const int begin, const int end, int vert) {
        if (begin < 0 || begin >= size_ver || end < 0 || end >= size_ver) {
            cerr << "Error in addEdge(" << begin << ", " << end << ")\n";
            throw out_of_range("Error in addEdge");
        }

        if (mx[begin][end])
            return;
        size_adg++;
        size_ver++;
        mx[begin][end] = vert;
        mx[end][begin] = vert;
    }


    void Print_mr() {
        for (int i = 0; i < this->size_ver; i++) {
            cout << "|";
            for (int j = 0; j < this->size_ver; j++) {
                cout << mx[i][j];
                if (j < size_ver-1)
                    cout << "   ";
            }
            cout << "|" << endl;
        }
        cout << endl;
    }

    vector<int>  Dijkstra(int start)
    {
        vector<int> distance(size_ver,1e9);
        vector<bool> visited(size_ver, false);
        distance[start]=0;
        int index;
        for (int count=0; count<size_ver-1; count++)
        {
            int min=1e9;
            for (int i=0; i<size_ver; i++)
                if (!visited[i] && distance[i]<=min)
                {
                    min=distance[i];
                    index=i;
                }
            visited[index]=true;
            for (int i=0; i<size_ver; i++)
                if (!visited[i] && mx[index][i] && distance[index]!=1e9 && distance[index]+mx[index][i]<distance[i])
                    distance[i]=distance[index]+mx[index][i];
        }

        cout<<"Shortest distances (Dijkstra):\t\n";
        for (int i=0; i<size_ver; i++)
            if (distance[i]!=1e9)
                cout<<start+1<<" -> "<<i+1<<" = "<<distance[i]<<endl;
            else cout<<start+1<<" -> "<<i+1<<" = "<<"error"<<endl;
        cout << endl;
        return distance;
    }

    void ostov_prim() {
        int edge = 0;
        vector<bool> selected(size_ver, false);
        selected[0] = true;
        int x;
        int y;
        cout<<"Ostov:\n";
        cout << "Edge" << " : " << "Weight";
        cout << endl;
        while (edge < size_ver - 1) {
            int min = 1e9;
            x = 0;
            y = 0;
            for (int i = 0; i < size_ver; i++) {
                if (selected[i]) {
                    for (int j = 0; j < size_ver; j++) {
                        if (!selected[j] && mx[i][j]) {
                            if (mx[i][j] < min ) {
                                min = mx[i][j];
                                x = i;
                                y = j;
                            }

                        }
                    }
                }
            }
            cout << x+1 << " -> " << y+1 << " :  " << mx[x][y];
            cout << endl;
            selected[y] = true;
            edge++;
        }
        cout << endl;
    }

};


Graph_mr generateGraph_M(int size)
{
    vector<vector<int>> mx(size);
    random_device rd;
    mt19937 mersenne(rd());
    for (int i = 0; i < size; i++)
    {
        mx[i].resize(size, 0);
        for (int j = 0; j < size; j++)
            if (mersenne() %  3)
                mx[i][j] = int(mersenne() %  3);
            else
                mx[i][j] = 0;
        mx[i][i] = 0;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            mx[i][j] = mx[j][i];
    }

    Graph_mr graph(mx);
    return graph;
}



