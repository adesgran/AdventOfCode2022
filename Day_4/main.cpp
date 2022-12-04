#include <iostream>
#include <fstream>
#include <string>

bool    contains(std::string str) //Part 1
{
    size_t pos = str.find(',');
    if (pos == std::string::npos)
    {
        std::cout << "Wrong input" << std::endl;
        return (false);
    }
    std::string s1 = str.substr(0, pos);
    std::string s2 = str.substr(pos + 1, str.length() - pos);
    
    int a1 = std::stoi(s1.substr(0, s1.find('-')));
    int a2 = std::stoi(s1.substr(s1.find('-') + 1, s1.length() - s1.find('-')));
    int b1 = std::stoi(s2.substr(0, s2.find('-')));
    int b2 = std::stoi(s2.substr(s2.find('-') + 1, s2.length() - s2.find('-')));

    if ( ( a1 <= b1 && a2 >= b2 ) || ( a1 >= b1 && a2 <= b2 ) )
        return (true);
    return (false);
}

bool overlap(std::string str) //Part 2
{
    size_t pos = str.find(',');
    if (pos == std::string::npos)
    {
        std::cout << "Wrong input" << std::endl;
        return (false);
    }
    std::string s1 = str.substr(0, pos);
    std::string s2 = str.substr(pos + 1, str.length() - pos);
    
    int a1 = std::stoi(s1.substr(0, s1.find('-')));
    int a2 = std::stoi(s1.substr(s1.find('-') + 1, s1.length() - s1.find('-')));
    int b1 = std::stoi(s2.substr(0, s2.find('-')));
    int b2 = std::stoi(s2.substr(s2.find('-') + 1, s2.length() - s2.find('-')));

    if ( ( a1 <= b1 && a2 >= b1 ) || ( a1 <= b2 && a2 >= b2 ) ||
         (b1 <= a1 && b2 >= a1) || (b1 <= a2 && b2 >= a2) )
        return (true);
    return (false);
}

int main()
{
    int res_contains = 0;
    int res_overlap = 0;
    std::string line;

    std::ifstream myfile1 ("input.txt");
    if (myfile1.is_open())
    {
        while ( getline (myfile1,line) )
        {
            if (line.length() < 7)
                continue;
            if (contains(line))
                res_contains++;
            if (overlap(line))
                res_overlap++;
        }
    }
    std::cout << "Result 1 : " << res_contains << std::endl;
    std::cout << "Result 2 : " << res_overlap << std::endl; 
    myfile1.close();

    return (0);
}