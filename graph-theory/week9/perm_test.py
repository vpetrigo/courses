#!/usr/bin/env python3
# coding=utf-8


import unittest
import permute


class PermuteTest(unittest.TestCase):
    def test_phi_founder(self):
        test_files = ("test25", "test26", "test27", "test32", "test34")
        ans_list = (2, 15, 18, 2, 0)
        i = 0

        for f in test_files:
            with self.subTest(msg="File: " + str(f)):
                with open(f) as tf:
                    reader = permute.read_data(tf)
                    s, a = next(reader), next(reader)
                    p = permute.find_phi(s, a)
                    self.assertEqual(permute.count_holes(s, a, p), ans_list[i])
                    i += 1


if __name__ == '__main__':
    unittest.main()
