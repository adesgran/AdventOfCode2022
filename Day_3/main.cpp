#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

int convertToInt(char c)
{
    if (c == std::tolower(c))
        return (c - 'a' + 1);
    else
        return (c - 'A' + 27);
    return (0);
}

int main()
{
    int res = 0;
    std::string line;

    //Solution For Part 1
    std::ifstream myfile1 ("input.txt");
    if (myfile1.is_open())
    {

        while ( getline (myfile1,line) )
        {
            std::string first = line.substr(0, line.length()/2);
            std::string second = line.substr(line.length()/2, line.length()/2);
            for (std::string::iterator it = first.begin(); it != first.end(); it++)
            {
                if (std::find(second.begin(), second.end(), *it) != second.end())
                {
                    res += convertToInt(*it);
                    break;
                }
            }
        }
    }
    std::cout << "Result 1 : " << res << std::endl;
    myfile1.close();

    //Solution For Part 2
    res = 0;
    std::vector<std::string> vec;
    std::ifstream myfile2 ("input.txt");
    if (myfile2.is_open())
    {

        while ( getline (myfile2,line) )
        {
            vec.push_back(line);
            if (vec.size() == 3)
            {
                for (std::string::iterator it = vec[0].begin(); it != vec[0].end(); it++)
                {
                    if (std::find(vec[1].begin(), vec[1].end(), *it) != vec[1].end() && std::find(vec[2].begin(), vec[2].end(), *it) != vec[2].end())
                    {
                        res += convertToInt(*it);
                        break;
                    }
                }
                vec.clear();
            }
        }
    }
    std::cout << "Result 2 : " << res << std::endl;
    myfile2.close();
    return (0);
}