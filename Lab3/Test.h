#include "Graph_mr.h"
#include "Graph_ms.h"

void Test_Ford_Bellman()
{
    vector<vector<bool>> mx =     {{0, 1, 0, 1, 1, 1},
                                   {1, 0, 1, 0, 0, 0},
                                   {0, 1, 0, 1, 0, 1},
                                   {1, 0, 1, 0, 1, 0},
                                   {1, 0, 0, 1, 0, 1},
                                   {1, 0, 1, 0, 1, 0}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0), Vertex(1, 1, 1)};
    Graph_ms graph(mx, verts);

    vector<double> ans0 = {0.0, 2.0, 2 + sqrt(2), sqrt(8), 2.0, sqrt(3)};
    if (ans0 == graph.Ford_Bellman(0))
    {
        cout <<  "Test_Ford_Bellman: PASSED" << endl << endl;
    }
    else
        cout <<  "Test_Ford_Bellman: ERROR" << endl << endl;
}

void Test_Ford_Bellman_new()
{
    vector<vector<bool>> mx =     {{0, 1, 0, 1, 1, 1},
                                   {1, 0, 1, 0, 0, 0},
                                   {0, 1, 0, 1, 0, 1},
                                   {1, 0, 1, 0, 1, 0},
                                   {1, 0, 0, 1, 0, 1},
                                   {1, 0, 1, 0, 1, 0}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0), Vertex(1, 1, 1)};
    Graph_ms graph(mx, verts);

    vector<double> ans0 = {0.0, 2.0, 2 + sqrt(2), sqrt(8), 2.0, sqrt(3)};
    if (ans0 == graph.Ford_Bellman_new(0))
    {
        cout <<  "Test_Ford_Bellman_new: PASSED" << endl << endl;
    }
    else
        cout <<  "Test_Ford_Bellman_new: ERROR" << endl << endl;
}


void Test_Dijkstra()
{
    vector<vector<int>> mx =      {{0, 0, 4, 6, 0, 0},
                                   {0, 0, 1, 0, 0, 2},
                                   {4, 1, 0, 0, 7, 0},
                                   {6, 0, 0, 0, 4, 0},
                                   {0, 0, 7, 4, 0, 3},
                                   {0, 2, 0, 0, 3, 0}};
    vector<int> ans0 = {0, 5, 4, 6, 10, 7};
    Graph_mr graph(mx);
    if (ans0 == graph.Dijkstra(0))
    {
        cout <<  "Test_Dijkstra: PASSED" << endl << endl;
    }
    else
        cout <<  "Test_Dijkstra: ERROR" << endl << endl;
}

void Test_ostov()
{
    vector<vector<int>> mx =      {{0, 0, 4, 6, 0, 0},
                                   {0, 0, 1, 0, 0, 2},
                                   {4, 1, 0, 0, 7, 0},
                                   {6, 0, 0, 0, 4, 0},
                                   {0, 0, 7, 4, 0, 3},
                                   {0, 2, 0, 0, 3, 0}};
    vector<int> ans0 = {0, 5, 4, 6, 10, 7};
    Graph_mr graph(mx);
    graph.ostov_prim();
}




void TestAll()
{
    Test_Ford_Bellman();
    Test_Ford_Bellman_new();
    Test_Dijkstra();
    Test_ostov();

}
