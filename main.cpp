#include "graph_include.h"
#include "Brute.cpp"
#include "greedy.cpp"
#include "BranchandBound.cpp"

// #include <opencv2/opencv.hpp>

int main()
{
    n = getmatrix();

    vector<vector<int>> edge_list = GreedyApproach(graph);
    auto [full, g] = makeUgraph();

    rendergraph(full, -1);
    system("dot -Tpng a.dot -o ./Graphs/original.png");

    string render = "";
    int currentCost = 0;
    for (int j = 0; j < n; j++)
    {
        vector<int> edge = edge_list[j];

        changeStyle(g, edge[0], edge[1], emp);
        changeColor(g, edge[0], edge[1], red);
        changeColor(full, edge[0], edge[1], red);
        currentCost += edge[2];
        rendergraph(g, currentCost);
        changeColor(g, edge[0], edge[1], black);
        render = "dot -Tpng a.dot -o ./Graphs/img" + to_string(j) + ".png";
        system(render.c_str());
    }
    rendergraph(full, -1);
    system("dot -Tpng a.dot -o ./Graphs/final.png");
    currentCost = 0;
}