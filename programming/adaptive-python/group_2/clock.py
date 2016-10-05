#!/usr/bin/env python3
# coding=utf-8



def main():
    seconds = int(input())
    clock_s = seconds % 60
    clock_m = seconds // 60 % 60
    clock_h = seconds // 60 // 60 % 24

    print("{}:{:02}:{:02}".format(clock_h, clock_m, clock_s))


if __name__ == "__main__":
    main()
