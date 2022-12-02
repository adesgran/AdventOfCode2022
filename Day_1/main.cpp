#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> vec;
    std::string line;
    std::ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        int sum = 0;

        while ( getline (myfile,line) )
        {
            if (line.length() > 0)
                sum += std::stoi(line);
            else
            {
                vec.push_back(sum);
                sum = 0;
            }
        }
    }
    std::sort(vec.begin(), vec.end());
    std::cout << "Maximum : " << vec.back() << std::endl;
    std::cout << "Sum of 3 maximums : " << vec[vec.size()-1] + vec[vec.size()-2] + vec[vec.size()-3] << std::endl;
    
    return (0);
}