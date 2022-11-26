#include <vector>
#include <climits>
#include <iostream>
using namespace std;

class permute
{
private:
    int n;
    int k = n - 2;
    int l = n - 2;
    void swap(vector<int>::iterator i, vector<int>::iterator j)
    {
        int temp = *j;
        *j = *i;
        *i = temp;
    }

public:
    vector<int> v;
    permute(int n)
    {
        this->n = n;
        for (int i = 0; i < n; i++)
            v.push_back(i);
    }
    bool next_permute()
    {
        if (v.size() == 0)
            return false;

        vector<int>::iterator i = v.end() - 1, j = v.end() - 1;
        while (i > v.begin() && *(i - 1) >= *i)
            --i;

        if (i == v.begin())
            return false;

        while (*j <= *(i - 1))
            --j;

        swap(i - 1, j);

        j = v.end() - 1;
        while (i < j)
        {
            swap(i, j);
            i++;
            j--;
        }
        return true;
    }
};

vector<vector<int>> BruteForce(vector<vector<int>> const &g)
{
    int current_distance = 0, minDistance = INT_MAX;
    int n = g.size();
    vector<int> shortest_path;
    permute p(n);

    do
    {
        int i;
        for (i = 0; i < n - 1; i++)
            current_distance += g[p.v[i]][p.v[i + 1]];
        current_distance += g[p.v[i]][p.v[0]];

        if (current_distance < minDistance)
        {
            minDistance = current_distance;
            shortest_path = p.v;
        }

        current_distance = 0;

    } while (p.next_permute());

    vector<vector<int>> edge_list;
    auto itr = shortest_path.begin();
    for (; itr != shortest_path.end() - 1; itr++)
    {
        vector<int> temp = {*itr, *(itr + 1), g[*itr][*(itr + 1)]};
        edge_list.push_back(temp);
    }
    vector<int> temp = {*itr, shortest_path.front(), g[*itr][shortest_path.front()]};
    edge_list.push_back(temp);

    return edge_list;
}