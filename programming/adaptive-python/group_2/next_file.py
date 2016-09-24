#!/usr/bin/env python3
# coding=utf-8

import urllib.request as req


def main():
    base_url = "https://stepic.org/media/attachments/course67/3.6.3/"

    with open("dataset_28254_1.txt") as link_file:
        url = link_file.readline().strip()

    found = False
    content = ""

    while not found:
        next_file = req.urlopen(url)
        first_line = next_file.readline().decode()

        if first_line[:2] != "We":
            url = base_url + first_line.strip()
        else:
            found = True
            content += first_line
            content += "".join((line.decode() for line in next_file))

    with open("next_file_content.txt", "w") as nfc:
        print(content, file=nfc)


if __name__ == "__main__":
    main()
