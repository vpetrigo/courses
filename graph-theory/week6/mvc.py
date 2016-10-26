def maximal_matching(graph, v1):
    def find_vertex_in_matching(v):
        for i in range(len(matching)):
            if matching[i][0] == v:
                return i, 1
            elif matching[i][1] == v:
                return i, 0
        return None

    def find_augmenting_path(i):
        def dfs(v):
            nonlocal augm_path_is_found
            used[v] = 1
            for w in graph[v]:
                if not used[w] and not augm_path_is_found:
                    temp = find_vertex_in_matching(w)
                    if temp is None:
                        augm_path.append(w)
                        augm_path_is_found = True
                    else:
                        j, part = temp[0], temp[1]
                        used[w] = 1
                        dfs(matching[j][part])
                        if augm_path_is_found:
                            augm_path.append(w)
            if augm_path_is_found:
                augm_path.append(v)

        if find_vertex_in_matching(i) is None:
            used = [0 for _ in range(len(graph))]
            augm_path = []
            augm_path_is_found = False
            dfs(i)
            if augm_path_is_found:
                return augm_path[::-1]
            else:
                return None

    matching = []
    for i in range(v1):
        augmenting_path = find_augmenting_path(i)
        if augmenting_path is not None:
            for j in range(len(augmenting_path) - 1):
                mt = sorted([augmenting_path[j], augmenting_path[j + 1]])
                if mt not in matching:
                    matching.append(mt)
                else:
                    matching.remove(mt)

    return matching


def minimal_vertex_cover(graph, v1):
    def dfs(v):
        used[v] = 1
        for w in dgraph[v]:
            if not used[w]:
                dfs(w)

    def in_matching(v):
        for i in range(len(mt)):
            if mt[i][0] == v:
                return True
        return False

    mt = maximal_matching(graph, v1)
    dgraph = [[] for _ in range(len(graph))]

    for i in range(v1):
        for j in range(len(graph[i])):
            edge = [i, graph[i][j]]
            if edge in mt:
                dgraph[edge[1]].append(edge[0])
            else:
                dgraph[edge[0]].append(edge[1])

    used = [0 for _ in range(len(dgraph))]
    for i in range(v1):
        if not in_matching(i):
            dfs(i)

    mvc = []

    for i in range(len(used)):
        if i < v1 and not used[i] or i >= v1 and used[i]:
            mvc.append(i)

    return mvc


v1, v2, e = map(int, input().split())
print(v1, v2, e)
graph = [[] for _ in range(v1 + v2)]
for _ in range(e):
    x, y = map(int, input().split())
    print(x, y)
    graph[x].append(y)
    graph[y].append(x)

print(*minimal_vertex_cover(graph, v1))