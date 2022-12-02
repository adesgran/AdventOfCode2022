#include <iostream>
#include <fstream>
#include <string>

int previous(int n)
{
    if (n == 1)
        return 3;
    else
        return n - 1;
}

int next(int n)
{
    if (n == 3)
        return 1;
    else
        return n + 1;
}

int rps1(char p1, char p2)
{
    int s1 = (int)(p1 - 'A') + 1;
    int s2 = (int)(p2 - 'X') + 1;

    if (s1 == s2)
        return (s2 + 3);
    else if (s1 == previous(s2))
        return (s2 + 6);
    return (s2);
}

int rps2(char p1, char p2)
{
    int s1 = (int)(p1 - 'A' + 1);
    int s2 = (int)(p2 - 'X' + 1);

    if (s2 == 1)
        return (previous(s1));
    else if (s2 == 2)
        return (s1 + 3);
    else if (s2 == 3)
        return (next(s1) + 6);
    return (0);
}

int main()
{
    int score1 = 0;
    int score2 = 0;
    std::ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        std::string line;
        while ( getline (myfile,line) )
        {
            score1 += rps1(line[0], line[2]);
            score2 += rps2(line[0], line[2]);
        }
    }
    std::cout << "Points for the first game : " << score1 << std::endl;
    std::cout << "Points for the second game : " << score2 << std::endl;
    return (0);
}