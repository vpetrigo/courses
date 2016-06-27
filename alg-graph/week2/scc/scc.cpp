#include <iostream>
#include <vector>

using GraphRepr = std::vector<std::vector<int>>;

void fill_graph(int edges, GraphRepr& graph); 
GraphRepr make_reverse_graph(const GraphRepr& graph);
void dfs(const GraphRepr& graph);
void explore(const GraphRepr& graph, int vertice, std::vector<VerticeStatus>& visited,
             std::vector<int>& pre, std::vector<int>& post);

int main() {
    int n, m;
    std::cin >> n >> m;
    GraphRepr graph(n);

    fill_graph(m, graph);
    auto graph_r = make_reverse_graph(graph);
    
    
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

