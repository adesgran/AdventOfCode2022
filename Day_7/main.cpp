#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

class directory
{
    public :
        directory( std::string name, directory * parent = NULL ) : _name(name), _parent(parent) {};
        ~directory() {
            _subdirs.clear();
            _files.clear();
        };

        void ls( std::vector< std::string > lines )
        {
            for ( std::vector< std::string >::iterator it = lines.begin(); it < lines.end(); it++ )
            {
                std::string line = *it;
                std::string type = line.substr(0, line.find_first_of(" "));
                if ( type == "dir" )
                {
                    std::string name = line.substr(line.find_first_of(" ") + 1);
                    bool exists = false;
                    for ( std::vector< directory >::iterator it = _subdirs.begin(); it < _subdirs.end(); it++ )
                    {
                        if ( it->get_name() == name )
                        {
                            exists = true;
                            break;
                        }
                    }
                    if ( !exists )
                        _subdirs.push_back( directory( name, this ) );
                }
                else
                {
                    std::string name = line.substr(line.find_first_of(" ") + 1, line.find_last_of(" "));
                    int size = std::stoi( line.substr( 0, line.find_first_of(" ") ) );
                    bool exists = false;
                    for ( std::vector< std::pair< std::string, int > >::iterator it = _files.begin(); it < _files.end(); it++ )
                    {
                        if ( it->first == name )
                        {
                            exists = true;
                            break;
                        }
                    }
                    if ( !exists )
                        _files.push_back( std::make_pair( name, size ) );
                }
            }
        }

        directory * cd( std::string name )
        {
            if ( name == ".." )
            {
                return _parent;
            }
            else
            {
                for ( std::vector< directory >::iterator it = _subdirs.begin(); it < _subdirs.end(); it++ )
                {
                    if ( it->get_name() == name )
                    {
                        return &(*it);
                    }
                }
                std::cout << "Directory " << name << " does not exist" << std::endl;
            }
            return NULL;
        }

        std::string get_name() { return _name; };
        directory * get_parent() { return _parent; };
        std::vector< directory > get_subdirs() { return _subdirs; };
        std::vector< std::pair< std::string, int > > get_files() { return _files; };

        int get_size()
        {
            int size = 0;
            for ( std::vector< std::pair< std::string, int > >::iterator it = _files.begin(); it < _files.end(); it++ )
            {
                size += it->second;
            }
            for ( std::vector< directory >::iterator it = _subdirs.begin(); it < _subdirs.end(); it++ )
            {
                size += it->get_size();
            }
            return size;
        }
    
        void print_tree( std::string prefix = "- " )
        {
            std::cout << prefix << _name << " (dir)" << std::endl;
            prefix = "  " + prefix;
            for ( std::vector< std::pair< std::string, int > >::iterator it = _files.begin(); it < _files.end(); it++ )
            {
                std::cout << prefix << it->first << " (file, size=" << it->second << std::endl;
            }
            for ( std::vector< directory >::iterator it = _subdirs.begin(); it < _subdirs.end(); it++ )
            {
                it->print_tree( prefix );
            }
        }

        int get_part1()
        {
            int res = 0;
            int size = this->get_size();
            if ( size <= 100000 )
                res += size;
            for ( std::vector< directory >::iterator it = _subdirs.begin(); it < _subdirs.end(); it++ )
                res += it->get_part1();
            return res;
        }

        int get_sum()
        {
            int res = 0;
            for ( std::vector< std::pair< std::string, int > >::iterator it = _files.begin(); it < _files.end(); it++ )
            {
                res += it->second;
            }
            for ( std::vector< directory >::iterator it = _subdirs.begin(); it < _subdirs.end(); it++ )
            {
                res += it->get_sum();
            }
            return res;
        }

        int get_part2( int to_free )
        {
            int dir_size = this->get_size();
            int res = 0;
            if ( dir_size >= to_free )
                res = dir_size;
            for ( std::vector< directory >::iterator it = _subdirs.begin(); it < _subdirs.end(); it++ )
            {
                int subdir_res = it->get_part2( to_free );
                if ( subdir_res >= to_free && subdir_res > 0)
                {
                    res = subdir_res;
                }
            }
            return res;
        }
    
    private :
        std::string _name;
        directory * _parent;
        std::vector< directory > _subdirs;
        std::vector< std::pair< std::string, int > > _files;
};

int main()
{
    directory root( "/" );
    directory * current = &root;
    std::vector< std::string > args;
    std::string line;
    std::ifstream myfile1 ("input.txt");
    if (myfile1.is_open())
    {
        while ( getline (myfile1,line) )
        {
            if ( line[0] == '$')
            {
                if ( args.size() )
                {
                    current->ls( args );
                    args.clear();
                }
                line = line.substr( 2 );
                std::string cmd = line.substr(0, line.find_first_of(" "));
                if ( cmd == "cd" )
                {
                    directory * next;
                    if ( line.find_first_of(" ") == std::string::npos || line.substr( line.find_first_of(" ") + 1 ) == "/" )
                    {
                        current = &root;
                        continue;
                    }
                    else
                        next = current->cd( line.substr( line.find_first_of(" ") + 1 ) );
                    if ( next )
                        current = next;
                }
            }
            else
            {
                args.push_back( line );
            }
        }
        if ( args.size() )
        {
            current->ls( args );
            args.clear();
        } 
        std::cout << "Part 1 res: " << root.get_part1() << std::endl;
        int to_free = root.get_sum() - 40000000;
        std::cout << "Part 2 res: " << root.get_part2( to_free ) << std::endl;

    } 
    myfile1.close();

    return (0);
}