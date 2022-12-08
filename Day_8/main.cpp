#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

int    n_visible(std::vector< std::vector < int > > &data, int x, int y)
{
    int res = 4;

    for (int i = 0; i < x; i++)
    {
        if ( data[i][y] >= data[x][y] )
        {
            res--;
            break;
        }
    }
    for ( int i = x + 1; i < (int)data.size(); i++ )
    {
        if ( data[i][y] >= data[x][y] )
        {
            res--;
            break;
        }
    }
    for ( int i = 0; i < y; i++ )
    {
        if ( data[x][i] >= data[x][y] )
        {
            res--;
            break;
        }
    }
    for ( int i = y + 1; i < (int)data[x].size(); i++ )
    {
        if ( data[x][i] >= data[x][y] )
        {
            res--;
            break;
        }
    }
    return (res?1:0);
}

int scenic_value(std::vector< std::vector < int > > &data, int x, int y)
{
    int res = 1;
    int tmp = 0;

    for ( int i = x - 1; i >= 0; i-- )
    {
        tmp++;
        if ( data[i][y] >= data[x][y] )
            break;
    }
    res *= tmp;
    tmp = 0;
    for ( int i = x + 1; i < (int)data.size(); i++ )
    {
        tmp++;
        if ( data[i][y] >= data[x][y] )
            break;
    }
    res *= tmp;
    tmp = 0;
    for ( int i = y - 1; i >= 0; i-- )
    {
        tmp++;
        if ( data[x][i] >= data[x][y] )
            break;
    }
    res *= tmp;
    tmp = 0;
    for ( int i = y + 1; i < (int)data[x].size(); i++ )
    {
        tmp++;
        if ( data[x][i] >= data[x][y] )
            break;
    }
    res *= tmp;
    return (res);
}

int main()
{
    std::vector< std::vector < int > > data;
    std::string line;
    std::ifstream myfile1 ("input.txt");
    int res1 = 0;
    int res2 = 0;
    
    if (myfile1.is_open())
    {
        while ( getline (myfile1,line) )
        {
            std::vector < int > tmp;
            for ( std::string::iterator it = line.begin(); it < line.end(); it++ )
            {
                if ( isdigit(*it) )
                    tmp.push_back( *it - '0' );
            }
            data.push_back(tmp);
        }
        myfile1.close();
        for (int i = 0; i < (int)data.size(); i++)
        {
            for (int j = 0; j < (int)data[i].size(); j++)
            {
                res1 += n_visible(data, i, j);
                int tmp = scenic_value(data, i, j);
                if ( tmp > res2 )
                    res2 = tmp;
            }
        }

        std::cout << "Result 1: " << res1 << std::endl;
        std::cout << "Result 2: " << res2 << std::endl;
    } 
    myfile1.close();

    return (0);
}