#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <climits>
#include <boost/graph/graphviz.hpp>

std::vector<std::vector<int>> graph;
int n;
const std::string black = "black", red = "red", white = "white", invis = "invis", emp = "", none = "none";

struct VertexProps
{
    int fontsize;
    std::string color;
    auto key() const { return std::tie(color); }
    bool operator<(const VertexProps &rhs) const { return std::tie(color) < std::tie(rhs.color); }
};
struct EdgeProps
{
    int weight;
    std::string dir = "none";
    std::string style = "invis";
    std::string color;
    std::string fontcolor;
    bool operator<(const EdgeProps &rhs) const { return std::tie(weight, dir, style, color, fontcolor) < std::tie(rhs.weight, rhs.dir, rhs.style, rhs.color, rhs.fontcolor); }
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              VertexProps, EdgeProps>
    Ugraph;

int getmatrix()
{
    std::ifstream f;
    f.open("matrix.txt");
    std::string line;
    while (getline(f, line))
    {
        std::istringstream lss(line);
        std::vector<int> temp;
        int tempint;
        while (lss >> tempint)
        {
            temp.push_back(tempint);
        }
        graph.push_back(temp);
    }
    return graph.size();
}

void changeStyle(Ugraph &g, int e1, int e2, const std::string style)
{
    g[boost::edge(e1, e2, g).first].style = style;
}

void changeColor(Ugraph &g, int e1, int e2, const std::string color)
{
    g[boost::edge(e1, e2, g).first].color = color;
    g[boost::edge(e1, e2, g).first].fontcolor = color;
}

std::tuple<Ugraph, Ugraph> makeUgraph()
{
    Ugraph full(n), g(n);

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            add_edge(j, i, {graph[i][j], none, emp, black, black}, full);
            add_edge(j, i, {graph[i][j], emp, invis, black, black}, g);
        }

    return {full, g};
}

void rendergraph(Ugraph g, int currentDistance)
{
    std::ofstream os("a.dot");
    std::string title;
    boost::dynamic_properties dp;
    dp.property("layout", boost::make_constant_property<Ugraph *>(std::string("circo")));
    dp.property("mindist", boost::make_constant_property<Ugraph *>(std::string("2.5")));
    dp.property("size", boost::make_constant_property<Ugraph *>(std::string("10, 10!")));
    dp.property("labelloc", boost::make_constant_property<Ugraph *>(std::string("t")));
    if (currentDistance != -1)
    {
        title = "Current Cost: " + std::to_string(currentDistance);
        dp.property("labeljust", boost::make_constant_property<Ugraph *>(std::string("r")));
    }
    else
    {
        title = "Original Graph";
        dp.property("labeljust", boost::make_constant_property<Ugraph *>(std::string("c")));
    }
    dp.property("label", boost::make_constant_property<Ugraph *>(std::string(title.c_str())));

    dp.property("node_id", boost::get(boost::vertex_index, g));
    dp.property("margin", boost::make_constant_property<Ugraph::edge_descriptor>(0.5));
    dp.property("dir", boost::get(&EdgeProps::dir, g));
    dp.property("style", boost::get(&EdgeProps::style, g));
    dp.property("headlabel", boost::get(&EdgeProps::weight, g));
    dp.property("taillabel", boost::get(&EdgeProps::weight, g));
    dp.property("color", boost::get(&EdgeProps::color, g));
    dp.property("fontcolor", boost::get(&EdgeProps::fontcolor, g));
    dp.property("penwidth", boost::make_constant_property<Ugraph::edge_descriptor>(2));
    dp.property("labeldistance", boost::make_constant_property<Ugraph::edge_descriptor>(3.5));
    dp.property("labelangle", boost::make_constant_property<Ugraph::edge_descriptor>(15));
    dp.property("fontsize", boost::make_constant_property<Ugraph::edge_descriptor>(11));
    write_graphviz_dp(os, g, dp);
}