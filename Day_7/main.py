class directory:
    _name = ""
    _root = None
    _parent = None
    _subdirs = []
    _files = []

    def __init__(self, name, parent = None, root = None):
        self._name = name
        self._parent = parent
        self._subdirs = []
        self._files = []
        if root == None:
            self._root = self
        else:
            self._root = root
    
    def ls(self, lines):
        for line in lines:
            args = line.split(" ")
            if (args[0] == "dir"):
                exists = False
                for sd in self._subdirs:
                    if sd._name == args[1]:
                        exists = True
                        print("Directory " + str(args[1]) + " already exists")
                        break
                if not exists:
                    self._subdirs.append(directory(args[1], self, self._root))
            else:
                exists = False
                for file in self._files:
                    if file[0] == args[1]:
                        exists = True
                        print("File " + str(args[1]) + " already exists")
                        break
                if not exists:
                    self._files.append([args[1], int(args[0])])
    
    def cd(self, dirname):
        if dirname == "/":
            return self._root
        if dirname == "..":
            if self._parent != None:
                return self._parent
            else:
                print("No parent directory")
        else:
            for subdir in self._subdirs:
                if subdir._name == dirname:
                    return subdir
            print(dirname + ": No such directory")
        return self
    
    def get_size(self):
        size = 0
        for file in self._files:
            size += int(file[1])
        for subdir in self._subdirs:
            size += subdir.get_size()
        return size
    
    def get_part1(self):
        res = self.get_size()
        if (res > 100000):
            res = 0
        for subdir in self._subdirs:
            res += subdir.get_part1()
        return res
    
    def get_part2(self, to_free):
        res = 0
        size = self.get_size()
        if (size < to_free):
            res = 0
        else:
            res = size
        for subdir in self._subdirs:
            subdir_res = subdir.get_part2(to_free)
            if (subdir_res < res and subdir_res > 0):
                res = subdir_res
        return res

def main():
    ls = []
    root = directory("/")
    curent = root
    with open("input.txt") as f:
        lines = f.read().splitlines() 
        for line in lines:
            if line == "\n":
                break
            args = line.split(" ")
            if (args[0] == "$"):
                if len(ls) > 0:
                    curent.ls(ls)
                    ls = []
                if (args[1] == "cd"):
                    curent = curent.cd(args[2])
            else:
                ls.append(line)
        if (len(ls) > 0):
            curent.ls(ls)
            ls = []
    print("Part 1 res: " + str(root.get_part1()))
    print("Part 2 res: " + str(root.get_part2(root.get_size() - 40000000)))  
    return (0)

if __name__ == "__main__":
    main()