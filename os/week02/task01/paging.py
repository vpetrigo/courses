#!/usr/bin/env python3
# coding=utf-8


import sys


def get_page(logical_addr: int):
    pml4 = (logical_addr >> 39) & 0x1ff
    dir_ptr = (logical_addr >> 30) & 0x1ff
    directory = (logical_addr >> 21) & 0x1ff
    table = (logical_addr >> 12) & 0x1ff
    offset = logical_addr & 0xfff

    return (pml4, dir_ptr, directory, table, offset)


def get_aligned_value(value: int):
    return ((value >> 12) & 0xffffffffff) << 12


def get_phy_addr(page: tuple, mem_struct: dict, cr3: int):
    value = cr3

    for i in range(len(page) - 1):
        index = page[i] * 8
        value = mem_struct.get(index + value, 0)

        if value & 1 == 0:
            print("fault")
            return

        value = get_aligned_value(value)

    print(value + page[-1])


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    mem_rows, queries, cr3 = next(reader)
    mem_struct = dict([next(reader) for _ in range(mem_rows)])

    for _ in range(queries):
        logical_addr, = next(reader)
        page = get_page(logical_addr)
        get_phy_addr(page, mem_struct, cr3)


if __name__ == "__main__":
    main()
