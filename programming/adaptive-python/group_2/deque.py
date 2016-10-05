#!/usr/bin/env python3
# coding=utf-8


import sys


class Deque(list):
    def push_front(self, x):
        super().insert(0, x)

    def pop_front(self):
        return self._pop(0)

    def push_back(self, x):
        super().append(x)

    def pop_back(self):
        return self._pop(-1)

    def _pop(self, index):
        if super().__len__() > 0:
            return super().pop(index)

        return -1


def main():
    reader = (line.strip() for line in sys.stdin)
    n_cmds = int(next(reader))
    deque = Deque()
    seq_ok = True
    func_to_call = [deque.push_front, deque.pop_front,
                    deque.push_back, deque.pop_back]

    for _ in range(n_cmds):
        cmd = tuple(map(int, next(reader).split()))

        if cmd[0] == 1 or cmd[0] == 3:
            func_to_call[cmd[0] - 1](cmd[1])
        elif cmd[0] == 2 or cmd[0] == 4:
            seq_ok = cmd[1] == func_to_call[cmd[0] - 1]()

        if not seq_ok:
            print("NO")
            break
    else:
        print("YES")


if __name__ == "__main__":
    main()
