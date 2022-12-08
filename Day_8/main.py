def n_visible(data, x, y):
    res = 4
    for i in range(0, x):
        if data[i][y] >= data[x][y]:
            res -= 1
            break
    for i in range(x+1, len(data)):
        if data[i][y] >= data[x][y]:
            res -= 1
            break
    for i in range(0, y):
        if data[x][i] >= data[x][y]:
            res -= 1
            break
    for i in range(y+1, len(data)):
        if data[x][i] >= data[x][y]:
            res -= 1
            break
    return (1 if res > 0 else 0)

def scenic_value(data, x, y):
    res = 1
    tmp = 0
    for i in range(x - 1, -1, -1):
        tmp += 1
        if data[i][y] >= data[x][y]:
            break
    res *= tmp
    tmp = 0
    for i in range(x + 1, len(data)):
        tmp += 1
        if data[i][y] >= data[x][y]:
            break
    res *= tmp
    tmp = 0
    for i in range(y - 1, -1, -1):
        tmp += 1
        if data[x][i] >= data[x][y]:
            break
    res *= tmp
    tmp = 0
    for i in range(y + 1, len(data)):
        tmp += 1
        if data[x][i] >= data[x][y]:
            break
    res *= tmp
    return res

def main():
    res1 = 0
    res2 = 0
    data = []
    with open("input.txt") as f:
        lines = f.read().splitlines() 
        for line in lines:
            tmp = []
            for i in line:
                tmp.append(int(i))
            data.append(tmp)
    for i in range(len(data)):
        for j in range(len(data[i])):
            res1 += n_visible(data, i, j)
            tmp = scenic_value(data, i, j)
            if tmp > res2:
                res2 = tmp
    print("Result 1: " + str(res1))
    print("Result 2: " + str(res2))

if __name__ == "__main__":
    main()