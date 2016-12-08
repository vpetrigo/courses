#!/usr/bin/env python3
# coding=utf-8


def get_field(n, m):
    def get_borders(index, max_val):
        v_min = index - 1 if index > 0 else index
        v_max = index + 1 if index + 1 < max_val else index

        return v_min, v_max

    def update_neigbours(i, j):
        l_h, r_h = get_borders(j, m)
        t_v, b_v = get_borders(i, n)

        for k in range(l_h, r_h + 1):
            for l in range(t_v, b_v + 1):
                field[l][k] += 1

    bomb_mark = "*"
    field = [[0] * m for _ in range(n)]
    mine_val = -6
    for i in range(n):
        line = input()

        for j in range(m):
            if line[j] == bomb_mark:
                field[i][j] = mine_val
                update_neigbours(i, j)
    return field


def main():
    n, m = map(int, input().split())
    num_field = get_field(n, m)
    ans = "\n".join("".join(str(y) if y >= 0 else "*" for y in x)
                    for x in num_field)

    print(ans)


if __name__ == "__main__":
    main()
