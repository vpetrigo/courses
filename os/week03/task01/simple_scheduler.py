n = input()

print(" ".join(map(lambda t: str(t[0]),
               sorted(enumerate(map(int, input().split())),
                      key=lambda t: t[1]))))
