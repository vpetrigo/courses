#!/usr/bin/env python3
# coding=utf-8


def main():
    shapes = {"1": "square", "2": "circle", "3": "triangle", "4": "rhombus"}
    shape = input()

    try:
        print("You have chosen a {}".format(shapes[shape]))
    except KeyError:
        print("There is no such shape!")


if __name__ == "__main__":
    main()
