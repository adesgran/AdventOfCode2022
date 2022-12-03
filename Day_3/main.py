def convertToInt(c):
    if c.islower():
        return ord(c) - 96
    return ord(c) - 64 + 26


#Solution For Part 1
res = int(0)
with open("input.txt") as f:
    lines = f.readlines()
    for line in lines:
        s1 = line[:len(line)//2]
        s2 = line[len(line)//2:]
        for i in range(len(s1)):
            if s1[i] in s2:
                res += convertToInt(s1[i])
                break
    print("Result 1 : " + str(res))

#Solution For Part 2
res = int(0)
vec = []
with open("input.txt") as f:
    lines = f.readlines()
    for line in lines:
        vec.append(line)
        if (len(vec) == 3):
            for i in range(len(vec[0])):
                if vec[0][i] in vec[1] and vec[0][i] in vec[2]:
                    res += convertToInt(vec[0][i])
                    break
            vec.clear()
    print("Result 2 : " + str(res))