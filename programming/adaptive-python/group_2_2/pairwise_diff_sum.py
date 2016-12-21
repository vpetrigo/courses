#!/usr/bin/env python3
# coding=utf-8


def main():
    num = int(input())
    rest = num
    int_list = []

    for i in range(1, num + 1):
        if rest - i <= i:
            int_list.append(rest)
            break
        else:
            int_list.append(i)
            rest -= i

    print("{}\n{}".format(len(int_list),
                          " ".join(str(x) for x in int_list)))


if __name__ == "__main__":
    main()
