#!/usr/bin/env python3
# coding=utf-8

import sys
import math


def main():
    reader = (int(line) for line in sys.stdin)
    percents, rubs, kops = reader
    kops += rubs * 100
    new_year_dep = kops + kops * percents / 100
    rubs = new_year_dep // 100
    kops = math.floor(new_year_dep % 100)
    print("{:d}\n{:d}".format(int(rubs), int(kops)))


if __name__ == "__main__":
    main()