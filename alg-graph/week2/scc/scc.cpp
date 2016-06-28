#include <iostream>
#include <vector>
#include <stack>
#include <utility>

using GraphRepr = std::vector<std::vector<int>>;
using ProcessStack = std::stack<int>;

void fill_graph(int edges, GraphRepr& graph); 
GraphRepr make_reverse_graph(const GraphRepr& graph);
void dfs(const GraphRepr& graph);
void explore(const GraphRepr& graph, int vertice, std::vector<bool>& visited,
             std::vector<int>& pre, std::vector<int>& post, int& time);

int main() {
    int n, m;
    std::cin >> n >> m;
    GraphRepr graph(n);

    fill_graph(m, graph);
    auto graph_r = make_reverse_graph(graph);
    dfs(graph); 
    
    return 0;
}

void fill_graph(int edges, GraphRepr& graph) {
    for (std::size_t i = 0; i < edges; ++i) {
        int u, v;
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

void dfs(const GraphRepr& graph) {
    int time = 1;
    std::vector<bool> visited(graph.size(), false);
    std::vector<int> pre, post;

    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            explore(graph, i, visited, pre, post, time);
        }
    }
}

void explore(const GraphRepr& graph, int vertice, std::vector<bool>& visited,
             std::vector<int>& pre, std::vector<int>& post, int& time) {
    ProcessStack proc_stack;

    proc_stack.push(vertice);

    while (!proc_stack.empty()) {
        auto proc_vertice = proc_stack.top();

        if (!visited[proc_vertice]) {
            std::cout << "PV: " << proc_vertice + 1;
            std::cout << " pre time: " << time++ << std::endl;
            visited[proc_vertice] = true;

            for (const auto& neighbour : graph[proc_vertice]) {
                if (!visited[neighbour]) {
                    proc_stack.push(neighbour);
                }
            }
        }
        else {
            std::cout << "PV: " << proc_vertice + 1;
            std::cout << " post time: " << time++ << std::endl;
            proc_stack.pop();
        }
    }
}
