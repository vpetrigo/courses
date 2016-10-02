#!/usr/bin/env python3
# coding=utf-8


import string


def count_init_messages(sequence):
    def get_alpha(seq):
        nonlocal count

        if len(seq) == 0:
            count += 1
            return

        for i in range(1, len(seq) + 1):
            if seq[:i] not in alph_table:
                break
            else:
                get_alpha(seq[i:])

    alphabet = " " + string.ascii_uppercase
    alph_table = {str(n): alph for n, alph in zip(range(len(alphabet)), alphabet)}
    count = 0
    get_alpha(sequence)

    return count


def count_messages_dp(seq):
    a1, a2 = 1, 1

    for i in range(1, len(seq)):
        a1, a2 = a1 + (a2 if 9 < int(seq[i - 1:i + 1]) < 27 else 0), a1

    return a1


def main():
    sequence = input().rstrip()
    print(count_messages_dp(sequence))


if __name__ == "__main__":
    main()
