class tab():
    data = []
    def __init__(self, line):
        self.data = []
        for i in range (0, len(line) // 4):
            self.data.append([])
    
    def add(self, line):
        for i in range (0, len(line) // 4):
            if line[4 * i + 1] != ' ':
                self.data[i].append(line[4 * i + 1])
    
    def move(self, n, _from, _to):
        for i in range (0, n):
            self.data[_to].append(self.data[_from].pop())
    
    def move_ordered(self, n, _from, _to):
        tmp = []
        for i in range (0, n):
            tmp.append(self.data[_from].pop())
        for i in range (0, n):
            self.data[_to].append(tmp.pop())
    
    def print(self):
        for i in range (0, len(self.data)):
            print(self.data[i])

def read_tab(lines):
    res = tab(lines[-1])
    for i in range (1, len(lines)):
        res.add(lines[i])
    return res

def follow_instruction(instruction, tab1):
    ins = instruction.split(" ")
    if (len(ins) < 6):
        print("Invalid instruction")
        return
    tab1.move(int(ins[1]), int(ins[3]) - 1, int(ins[5]) - 1)

def follow_instruction_oredered(instruction, tab1):
    ins = instruction.split(" ")
    if (len(ins) < 6):
        print("Invalid instruction")
        return
    tab1.move_ordered(int(ins[1]), int(ins[3]) - 1, int(ins[5]) - 1)

def main():
    with open("input.txt") as f:
        lines = f.readlines()
        tab_data = []
        for line in lines:
            if line == "\n":
                break
            tab_data.append(line)
        tab_data.reverse()
        tab1 = read_tab(tab_data)
        tab2 = read_tab(tab_data)
        lines = lines[len(tab_data) + 1:]
        for line in lines:
            follow_instruction(line, tab1)
            follow_instruction_oredered(line, tab2)
        tab1.print()
        print("")
        tab2.print()


if __name__ == "__main__":
    main()



    