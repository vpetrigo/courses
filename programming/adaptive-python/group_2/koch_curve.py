#!/usr/bin/env python3
# coding=utf-8


import turtle


def koch_turns(n):
    assert n >= 0

    if n == 0:
        return []

    rot = koch_turns(n - 1)
    rot += [60]
    rot += koch_turns(n - 1)
    rot += [-120]
    rot += koch_turns(n - 1)
    rot += [60]
    rot += koch_turns(n - 1)

    return rot


def turtle_koch_curve(n, line_length=10):
    for move in koch_turns(n):
        turtle.forward(line_length)
        turtle.left(move)
    turtle.forward(line_length)


def draw(n):
    turtle.color("red", "blue")
    turtle.begin_fill()
    turtle_koch_curve(n, 5)
    turtle.end_fill()
    turtle.done()


def main():
    n = int(input())
    draw(n)
    for i in koch_turns(n):
        print("turn", i)


if __name__ == "__main__":
    main()
