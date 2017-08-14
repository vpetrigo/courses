#!/usr/bin/env python3


def main():
    student_marks = input().strip().split()
    print("{:.2f}".format(student_marks.count("A") / len(student_marks)))


if __name__ == "__main__":
    main()