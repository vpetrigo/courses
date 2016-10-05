#!/usr/bin/env python3
# coding=utf-8


def is_valid_ip(ip_addr):
    def is_int(n):
        try:
            int(n)
            return True
        except:
            return False

    ip = ip_addr.split(".")
    valid_range = list(filter(lambda x: (len(x) > 0 and is_int(x) and
                                         0 <= int(x) <= 255), ip))

    if len(ip) == 4 and len(valid_range) == len(ip):
        return True

    return False


def main():
    ip_addr = input()
    if is_valid_ip(ip_addr):
        print("YES")
    else:
        print("NO")


if __name__ == "__main__":
    main()
