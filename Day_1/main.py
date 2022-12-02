res = int(0)
reslist = []
with open("input.txt") as f:
    lines = f.readlines()
    for line in lines:
        if line != "\n":
            res += int(line)
        else:
            reslist.append(res)
            res = 0
    print("Maximum : " + str(max(reslist)))
    print("Sum of 3 maximum : " + str(sum(sorted(reslist, reverse=True)[:3])))