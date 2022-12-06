def is_duplicate_char(str):
    for i in range (0, len(str)):
        for j in range (i + 1, len(str)):
            if str[i] == str[j]:
                return True
    return False

def get_start(line, size):
    for i in range (0, len(line) - size):
        str = line[i:i + size]
        if is_duplicate_char(str) == False:
            return i + size
    return -1

def main():
    with open("input.txt") as f:
        lines = f.readlines()
        for line in lines:
            if line == "\n":
                break
            res = get_start(line, 4)
            if res != -1:
                print("Start packet at position: " + str(res))
            else:
                print("No start packet found")
            res = get_start(line, 14)
            if res != -1:
                print("Start message at position: " + str(res))
            else:
                print("No start message found")
    return (0)

if __name__ == "__main__":
    main()