#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <functional>
#include <algorithm>

using VerticeType_t = unsigned;
using GraphRepr = std::vector<std::vector<VerticeType_t>>;
using NeighbourIt_t = GraphRepr::value_type::const_iterator;
using ProcessStack = std::stack<std::pair<VerticeType_t, NeighbourIt_t>>;
// pair of pre- and post-times
using VerticeTimeInfo = std::pair<unsigned, unsigned>;

enum class VerticeStatus { UNVISITED, PROCESSING, VISITED };

void fill_graph(std::size_t edges, GraphRepr& graph);
GraphRepr make_reverse_graph(const GraphRepr& graph);
std::vector<VerticeTimeInfo> dfs(const GraphRepr& graph);
void explore(const GraphRepr& graph, int vertice, std::vector<VerticeStatus>& visited,
             std::vector<VerticeTimeInfo> *time_info = nullptr, int *time = nullptr);
int count_conn_components(const GraphRepr& graph, const std::vector<VerticeTimeInfo>& time_inf);

int main() {
    std::size_t n, m;
    std::cin >> n >> m;
    GraphRepr graph(n);

    fill_graph(m, graph);
    auto graph_r = make_reverse_graph(graph);
    auto time_info = dfs(graph_r);
    std::cout << count_conn_components(graph, time_info) << std::endl;

    return 0;
}

void fill_graph(std::size_t edges, GraphRepr& graph) {
    for (std::size_t i = 0; i < edges; ++i) {
        VerticeType_t u, v;

        std::cin >> u >> v;
        graph[u - 1].emplace_back(v - 1);
    }
}

GraphRepr make_reverse_graph(const GraphRepr& graph) {
    auto graph_len = graph.size();
    GraphRepr graph_reverse(graph_len);

    for (std::size_t i = 0; i < graph_len; ++i) {
       for (const auto& vertice : graph[i]) {
           graph_reverse[vertice].emplace_back(i);
       }
    }

    return graph_reverse;
}

std::vector<VerticeTimeInfo> dfs(const GraphRepr& graph) {
    int time = 1;
    auto graph_len = graph.size();
    std::vector<VerticeTimeInfo> time_inf(graph_len, std::make_pair(0, 0));
    std::vector<VerticeStatus> visited(graph_len, VerticeStatus::UNVISITED);

    for (std::size_t i = 0; i < graph_len; ++i) {
        if (visited[i] == VerticeStatus::UNVISITED) {
            explore(graph, i, visited, &time_inf, &time);
        }
    }

    return time_inf;
}

void explore(const GraphRepr& graph, int vertice, std::vector<VerticeStatus>& visited,
             std::vector<VerticeTimeInfo> *time_info, int *time) {
    ProcessStack proc_stack;

    proc_stack.push(std::make_pair(vertice, graph[vertice].cbegin()));

    while (!proc_stack.empty()) {
        auto proc_vertice = proc_stack.top();

        if (visited[proc_vertice.first]) {
            std::cout << "PV: " << proc_vertice.first + 1;
            if (time) {
                std::cout << " pre time: " << *time;
            }
            std::cout << std::endl;
            visited[proc_vertice.first] = true;
            // fill previsited time
            if (time_info && time) {
                (*time_info)[proc_vertice.first].first = (*time)++;
            }

            for (const auto& neighbour : graph[proc_vertice.first]) {
                if (!visited[neighbour]) {
                    proc_stack.push(std::make_pair(neighbour, graph[neighbour].cbegin()));
                }
            }
        }
        else {
            std::cout << "PV: " << proc_vertice.first + 1;
            if (time) {
                std::cout << " post time: " << *time ;
            }
            std::cout << std::endl;
            // fill postvisited time
            if (time_info && time) {
                (*time_info)[proc_vertice.first].second = (*time)++;
            }
            proc_stack.pop();
        }
    }
}

int count_conn_components(const GraphRepr& graph, const std::vector<VerticeTimeInfo>& time_info) {
    auto graph_len = graph.size();
    std::vector<std::pair<int, int>> vertice_post(graph_len);
    std::vector<VerticeStatus> visited(graph_len, VerticeStatus::UNVISITED);
    unsigned conn_comp_counter = 0;

    for (std::size_t i = 0; i < graph_len; ++i) {
       vertice_post[i] = std::make_pair(time_info[i].second, i);
    }

    std::sort(vertice_post.begin(), vertice_post.end(), std::greater<std::pair<int, int>> ());
    for (std::size_t v = 0; v < graph_len; ++v) {
        if (visited[vertice_post[v].second] == VerticeStatus::UNVISITED) {
            ++conn_comp_counter;
            explore(graph, vertice_post[v].second, visited);
        }
    }

    return conn_comp_counter;
}
