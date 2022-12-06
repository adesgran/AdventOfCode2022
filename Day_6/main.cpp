#include <iostream>
#include <fstream>
#include <string>

bool    is_startstring(std::string str)
{
    for (std::string::size_type i = 0; i < str.size(); i++)
    {
        if ( str.rfind(str[i]) != i )
            return (false);
    }
    return (true);
}

int get_start(std::string line, std::string::size_type len)
{
    for (std::string::size_type i = 0; i <= line.size() - len; i++)
    {
        if ( is_startstring(line.substr(i, len)) )
            return (i + len);
    }
    return (-1);
}

int main()
{
    std::string line;
    std::ifstream myfile1 ("input.txt");
    if (myfile1.is_open())
    {
        while ( getline (myfile1,line) && line != "" )
        {
            if ( line != "")
            {
                int start = get_start(line, 4);
                if (start != -1)
                {
                    std::cout << "Start packet at position: " << start << std::endl;
                }
                else
                {
                    std::cout << "No start packet found" << std::endl;
                }
                start = get_start(line, 14);
                if (start != -1)
                {
                    std::cout << "Start message at position: " << start << std::endl;
                }
                else
                {
                    std::cout << "No start message found" << std::endl;
                }
            }
        }
    } 
    myfile1.close();

    return (0);
}