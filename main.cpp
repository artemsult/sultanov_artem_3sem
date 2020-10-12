#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>

using namespace std;

const int max_num_of_vertex = 5e4;
const int max_num_of_edges = 1e5;
const int Inf = 1e8;

class Graph
{
private:
    vector<vector<int>> data;
    int count_of_edges = 0;
    int count_of_vertexes = 0;
public:
    Graph(int count_of_vertexes_in, int count_of_edges_in)
    {
        data.reserve(count_of_vertexes_in);
        data.resize(count_of_vertexes_in);
        for (int i = 0; i < count_of_vertexes_in; ++i)
        {
            data[i].reserve(count_of_vertexes_in);
        }
        count_of_vertexes = count_of_vertexes_in;
        count_of_edges = count_of_edges_in;
    }
    void add_edge(int first_vertex, int second_vertex)
    {
        (*this).data[first_vertex - 1].push_back(second_vertex - 1);
        (*this).data[second_vertex - 1].push_back(first_vertex - 1);
        ((*this).count_of_edges)++;
    }
    void delete_edge(int first_vertex, int second_vertex);
    vector<int> find_shortest_way_1(int first_vertex, int second_vertex, vector<int>& ans)
    {
        int distances[(*this).count_of_vertexes] = {0};
        int parents[(*this).count_of_vertexes] = {0};
        bool used_vertexes[(*this).count_of_vertexes];
        for (int i = 0; i < (*this).count_of_vertexes; ++i)
        {
            used_vertexes[i] = false;
        }
        distances[first_vertex - 1] = 0;
        for (int i = 0; i < (*this).count_of_vertexes; ++i)
        {
            if (i != first_vertex - 1)
            {
                distances[i] = Inf;
            }
        }
        for (int i = 0; i < (*this).count_of_vertexes; ++i)
        {
            int current_vertex = 0;
            int min_distance = Inf + 1;
            for (int j = 0; j < (*this).count_of_vertexes; ++j)
            {
                if (min_distance > distances[j] && (used_vertexes[j] == false))
                {
                    min_distance = distances[j];
                    current_vertex = j;
                }
            }
            used_vertexes[current_vertex] = true;
            for (auto neighbour_of_current_vertex : (*this).data[current_vertex])
            {
                if (distances[neighbour_of_current_vertex] > distances[current_vertex] + 1)
                {
                    distances[neighbour_of_current_vertex] = distances[current_vertex] + 1;
                    parents[neighbour_of_current_vertex] = current_vertex;
                }

            }
        }
        if (used_vertexes[second_vertex - 1] == true && distances[second_vertex - 1] != Inf)
        {
            ans.reserve(distances[second_vertex - 1]);
            int current_vertex = second_vertex - 1;
            for (int i = 0; i < distances[second_vertex - 1]; ++i)
            {
                ans.push_back(current_vertex + 1);
                current_vertex = parents[current_vertex];
            }
            ans.push_back(first_vertex);
            reverse(ans.begin(), ans.end());
        }
        else
        {
            while(ans.size() != 0)
            {
                ans.pop_back();
            }
        }
        return ans;
    }
    vector<int> find_shortest_way_2(int first_vertex, int second_vertex, vector<int>& ans)
    {
        int start_vertex = first_vertex - 1;
        queue<int> q;
        q.push(start_vertex);
        vector<int> distances((*this).count_of_vertexes, (*this).count_of_vertexes);
        vector<int> parents((*this).count_of_vertexes);
        distances[start_vertex] = 0;
        parents[start_vertex] = -1;
        while (!q.empty())
        {
            int current_vertex = q.front();
            q.pop();
            for (int i = 0; i < (*this).data[current_vertex].size(); ++i)
            {
                int neighbour_of_current_vertex = (*this).data[current_vertex][i];
                if (distances[neighbour_of_current_vertex] > distances[current_vertex] + 1)
                {
                    q.push(neighbour_of_current_vertex);
                    distances[neighbour_of_current_vertex] = distances[current_vertex] + 1;
                    parents[neighbour_of_current_vertex] = current_vertex;

                }
            }
        }
        if (distances[second_vertex - 1] == (*this).count_of_vertexes)
        {
            while(ans.size() != 0)
            {
                ans.pop_back();
            }
        }
        else
        {
            int current_vertex = second_vertex - 1;
            for (int i = 0; i < distances[second_vertex - 1]; ++i)
            {
                ans.push_back(current_vertex + 1);
                current_vertex = parents[current_vertex];
            }
            ans.push_back(first_vertex);
            reverse(ans.begin(), ans.end());
        }
        return ans;
    }
    bool dfs(int current_vertex, int start_color, vector<int>& colors)
    {
        colors[current_vertex] = start_color;
//        for (int i = 0; i < (*this).count_of_vertexes; ++i)
//        {
//            cout << colors[i] << " ";
//        }
//        cout << "\n";
//        cout << current_vertex << "\n";
        bool ans = true;
        for (auto i : (*this).data[current_vertex])
        {
//            cout << "i=" << i << "\n";
//            cout << colors[i] << " " << start_color << "\n";
            if (colors[i] == 0)
            {
                colors[i] = 3 - start_color;
                ans = dfs(i, colors[i], colors);
            }
            else if (colors[i] == start_color)
            {
                return false;
            }
        }
        return ans;
    }
    bool is_bipartite()
    {
        bool ans = false;
        vector<int> colors;
        colors.reserve((*this).count_of_vertexes);
        for (int i = 0; i < (*this).count_of_vertexes; ++i)
        {
            colors.push_back(0);
        }
        int color = 1;
        for (int current_vertex = 0; current_vertex < (*this).count_of_vertexes; ++current_vertex)
        {
            if (colors[current_vertex] == 0)
            {
                if ((*this).dfs(current_vertex, color, colors) == false)
                {
                    return false;
                }
            }
        }
        return true;
    }
    friend std::istream& operator>> (std::istream &in, Graph &a);
    friend std::ostream& operator<< (std::ostream &out, const Graph &a);
};

std::istream& operator>> (std::istream &in, Graph &a)
{
    for (int i = 0; i < a.count_of_edges; ++i)
    {
        int first_vertex = 0, second_vertex = 0;
        cin >> first_vertex >> second_vertex;
        a.data[first_vertex - 1].push_back(second_vertex - 1);
        a.data[second_vertex - 1].push_back(first_vertex - 1);
    }
    return in;
}

int main()
{
    int count_of_edges = 0, count_of_vertexes = 0;
    cin >> count_of_vertexes >> count_of_edges;
    Graph graph(count_of_vertexes, count_of_edges);
    cin >> graph;
    graph.is_bipartite() ? cout << "YES" : cout << "NO";
    return 0;
}
