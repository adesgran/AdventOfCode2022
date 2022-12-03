def next(n):
    if n == 3:
        return 1
    return n + 1

def previous(n):
    if n == 1:
        return 3
    return n - 1

def rps1(p1, p2):
    p1 = ord(p1) - 64
    p2 = ord(p2) - 87
    if p1 == p2:
        return p2 + 3
    if p1 == previous(p2):
        return 6 + p2
    return p2

def rps2(p1, p2):
    p1 = ord(p1) - 64
    p2 = ord(p2) - 87
    if p2 == 1:
        return previous(p1)
    if p2 == 2:
        return 3 + p1
    return 6 + next(p1)


res1 = int(0)
res2 = int(0)
with open("input.txt") as f:
    lines = f.readlines()
    for line in lines:
        res1 += rps1(line[0], line[2])
        res2 += rps2(line[0], line[2])
    print("Points for the first game : " + str(res1))
    print("Points for the second game : " + str(res2))
        