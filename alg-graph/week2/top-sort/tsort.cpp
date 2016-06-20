#include <cstddef>
#include <iostream>
#include <vector>

using GraphRepr = std::vector<std::vector<int>>;

void fill_vector(const int m, GraphRepr& graph) {
    for (std::size_t i = 0; i < m; ++i) {
        int u, v;

        std::cin >> u >> v;
        graph[u - 1].emplace_back(v);
    }
}

void dfs(const GraphRepr& graph, std::vector<int>& post) {
    std::vector<bool> visited(graph.size(), false);
}

void topological_sort(const GraphRepr& graph) {
    std::vector<int> postorder(graph.size());
}

int main() {
    int n, m;
    std::cin >> n >> m;
    GraphRepr graph(n);
}
