def contains(str): #Part 1
    split_str = str.split(",")
    (s1, s2) = (split_str[0].split("-"))
    (s3, s4) = (split_str[1].split("-"))
    a1 = int(s1)
    a2 = int(s2)
    b1 = int(s3)
    b2 = int(s4)

    if (a1 <= b1 and a2 >= b2) or (a1 >= b1 and a2 <= b2):
        return True
    return False

def overlap(str): #Part 2
    split_str = str.split(",")
    (s1, s2) = (split_str[0].split("-"))
    (s3, s4) = (split_str[1].split("-"))
    a1 = int(s1)
    a2 = int(s2)
    b1 = int(s3)
    b2 = int(s4)

    if (a1 <= b1 and a2 >= b1) or (a1 <= b2 and a2 >= b2) or (b1 <= a1 and b2 >= a1) or (b1 <= a2 and b2 >= a2):
        return True
    return False

res_contains = int(0)
res_overlap = int(0)
with open("input.txt") as f:
    lines = f.readlines()
    for line in lines:
        if contains(line):
            res_contains += 1
        if overlap(line):
            res_overlap += 1
        
    print("Result 1 : " + str(res_contains))
    print("Result 2 : " + str(res_overlap))
