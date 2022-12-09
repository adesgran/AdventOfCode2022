#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

class map
{
    public:

        class coord
        {
            public:
                int x;
                int y;
                coord( void ) : x(0), y(0) {};
                coord( int x, int y ) : x(x), y(y) {};
                coord & operator=( coord const & co )
                {
                    x = co.x;
                    y = co.y;
                    return (*this);
                };
                coord( coord const & co )
                {
                    *this = co;
                };
                ~coord( void ) {};
                bool close( coord & co )
                {
                    if ( abs(x - co.x) <= 1 && abs(y - co.y) <= 1 )
                        return (true);
                    return (false);
                };
                bool operator==( coord & co )
                {
                    if ( x == co.x && y == co.y )
                        return (true);
                    return (false);
                };
        };
        

        class tail
        {
            public:
                coord   pos;
                tail    *previous;
                std::vector< coord > visited;
                tail( void ) : pos(coord()), previous(NULL) {};
                tail (tail *prev) : pos(prev->pos), previous(prev) {};
                tail (coord & co, tail *prev = NULL) : pos(co), previous(prev) {};
                tail & operator=( tail const & tl )
                {
                    pos = tl.pos;
                    previous = tl.previous;
                    return (*this);
                };
                ~tail( void ) {};

                void    visite( coord & co )
                {
                    for (std::vector< coord >::iterator it = visited.begin(); it != visited.end(); it++)
                    {
                        if ( *it == co )
                            return ;
                    }
                    visited.push_back(co);
                }

                void follow( coord &co )
                {
                    tail tl = tail(co);
                    previous = &tl;
                    follow();
                    previous = NULL;
                }

                void    follow( void )
                {
                    if (previous)
                    {
                        if (!previous->pos.close(pos))
                        {
                            if (abs(previous->pos.y - pos.y) == 2 && abs(previous->pos.x - pos.x) == 2)
                            {
                                if (previous->pos.y < pos.y)
                                {
                                    if (previous->pos.x < pos.x)
                                    {
                                        pos.y--;
                                        pos.x--;
                                    }
                                    else
                                    {
                                        pos.y--;
                                        pos.x++;
                                    }
                                }
                                else
                                {
                                    if (previous->pos.x < pos.x)
                                    {
                                        pos.y++;
                                        pos.x--;
                                    }
                                    else
                                    {
                                        pos.y++;
                                        pos.x++;
                                    }
                                }
                            }
                            else if (abs(previous->pos.x - pos.x) <= 1)
                            {
                                if (previous->pos.y < pos.y)
                                    {
                                        pos.x = previous->pos.x;
                                        pos.y--;
                                    }
                                else
                                    {
                                        pos.x = previous->pos.x;
                                        pos.y++;
                                    }
                            }
                            else
                            {
                                if (previous->pos.x < pos.x)
                                    {
                                        pos.y = previous->pos.y;
                                        pos.x--;
                                    }
                                else
                                    {
                                        pos.y = previous->pos.y;
                                        pos.x++;
                                    }
                            }
                        }
                    }
                    else
                        std::cout << "No previous" << std::endl;
                    visite(pos);
                }

                int count_visited( void )
                {
                    return (visited.size());
                }
        };

        map( void )
        {
            _head = coord(0, 0);
            _tails.push_back(tail());
            for (int i = 0; i < 8; i++)
                _tails.push_back(tail(&_tails.back()));


        };
        ~map( void ) {};

        void move( char c )
        {
            switch (c)
            {
                case 'U':
                    _head.y--;
                    break;
                case 'D':
                    _head.y++;
                    break;
                case 'L':
                    _head.x--;
                    break;
                case 'R':
                    _head.x++;
                    break;
            }
            _tails[0].follow(_head);
            for (int i = 1; i <= 8; i++)
                _tails[i].follow(_tails[i-1].pos);
            
        }

        void move( char c, int n )
        {
            for (int i = 0; i < n; i++)
                move(c);
            
        }

        void    print_res(void)
        {

            int res1 = _tails[0].count_visited();
            int res2 = _tails[8].count_visited();
            std::cout << "Part 1 : " << res1 << std::endl;
            std::cout << "Part 2 : " << res2 << std::endl;
        }

    private:
        unsigned int                        count;
        coord   _head;
        std::vector< tail >   _tails;
};

int main()
{
    std::string line;
    std::ifstream myfile1 ("input.txt");
    map m;
    
    if (myfile1.is_open())
    {
        while ( getline (myfile1,line) )
        {
            m.move(line[0], std::stoi(line.substr(2)));
        }
        m.print_res();
    } 
    myfile1.close();

    return (0);
}