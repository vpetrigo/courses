#!/usr/bin/env python3
# coding=utf-8


COMMANDS = ["stay", "up", "down", "left", "right"]


def main():
    cmd = int(input())

    try:
        resp = COMMANDS[cmd]
        if cmd < 0:
            # prohibit negative indexing
            raise IndexError
        elif resp == COMMANDS[0]:
            print("do not move")
        else:
            print("move {}".format(resp))
    except IndexError:
        print("error!")


if __name__ == "__main__":
    main()
