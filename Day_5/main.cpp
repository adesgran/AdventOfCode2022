#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

class pile
{
    public : 
        pile( void ) { _pile = std::vector<char>(); };
        pile( pile const & p ) : _pile(p._pile) {};
        pile operator=( pile & p ) { _pile = p._pile; return *this; };
        ~pile( void ) { _pile.clear(); };

        void add( char c ) { _pile.push_back(c); };
        void remove( void ) { _pile.pop_back(); };

        char get_last( void ) { return _pile.back(); };
        void remove_last( void ) { _pile.pop_back(); };

        void add_from( pile &p , int n )
        {
            for (int i = 0; i < n; i++)
            {
                if (p.size() == 0)
                {
                    std::cout << "Error: not enough cards in pile" << std::endl;
                    break;
                }
                this->add( p.get_last() );
                p.remove_last();
            }
        };

        void add_from_ordered( pile &p , int n )
        {
            if (p.size() == 0)
                {
                    std::cout << "Error: not enough cards in pile" << std::endl;
                    return ;
                }
            std::vector<char> tmp;
            for (int i = 0; i < n; i++)
            {
                tmp.push_back( p.get_last() );
                p.remove_last();
            }
            for (int i = tmp.size() - 1; i >= 0; i--)
            {
                this->add( tmp[i] );
            }
        };

        char operator[]( int i ) { return _pile[i]; };

        size_t size( void ) { return _pile.size(); };

    private :
        std::vector<char> _pile;
};

std::ostream &operator<<(std::ostream &os, pile &p)
{
    for (std::string::size_type i = 0; i < p.size(); i++)
    {
        os << "[" << p[i] << "] ";
    }
    return os;
}

std::vector<pile> read_tab( std::vector<std::string> tab )
{
    std::vector<pile> piles;
    for (std::string::size_type i = 0; i * 4 < tab.back().length() + 1; i++)
    {
        piles.push_back(pile());
        int j = tab.size() - 2;
        while (j >= 0 && tab[j][i * 4 + 1] != ' ')
        {
            piles[i].add(tab[j][i * 4 + 1]);
            j--;
        }

    }
    return piles;
}

bool    follow_instruction( std::string instruction, std::vector<pile> &piles )
{
    int n;
    int from;
    int to;
    try
    {
        n = std::stoi(instruction.substr(5, instruction.find("from") - 1));
        from = std::stoi(instruction.substr(instruction.find("from") + 5, instruction.find("to") - 1)) - 1;
        to = std::stoi(instruction.substr(instruction.find("to") + 3)) - 1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return (false);
    }

    piles[to].add_from(piles[from], n);

    return (true);
}

bool follow_instruction_ordered( std::string instruction, std::vector<pile> &piles )
{
    int n;
    int from;
    int to;
    try
    {
        n = std::stoi(instruction.substr(5, instruction.find("from") - 1));
        from = std::stoi(instruction.substr(instruction.find("from") + 5, instruction.find("to") - 1)) - 1;
        to = std::stoi(instruction.substr(instruction.find("to") + 3)) - 1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return (false);
    }

    piles[to].add_from_ordered(piles[from], n);

    return (true);
}

int main()
{
    std::vector<pile> piles;
    std::vector<pile> ordered_piles;
    std::string line;
    std::vector<std::string> tab;

    std::ifstream myfile1 ("input.txt");
    if (myfile1.is_open())
    {
        while ( getline (myfile1,line) && line != "" )
        {
            tab.push_back(line);
        }
        piles = read_tab(tab);
        for (std::vector<pile>::iterator it = piles.begin(); it != piles.end(); it++)
        {
            ordered_piles.push_back(pile(*it));
        }
        while ( getline (myfile1,line) )
        {
            if (!follow_instruction(line, piles) || !follow_instruction_ordered(line, ordered_piles))
                return (1);
        }
        //print piles
        for (std::string::size_type i = 0; i < piles.size(); i++)
        {
            std::cout << "pile " << i + 1 << " : " << piles[i] << std::endl;
        }
        std::cout << std::endl;
        for (std::string::size_type i = 0; i < ordered_piles.size(); i++)
        {
            std::cout << "ordered pile " << i + 1 << " : " << ordered_piles[i] << std::endl;
        }
    } 
    myfile1.close();

    return (0);
}