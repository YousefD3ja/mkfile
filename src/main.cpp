#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

typedef enum argtype
{
    null,
    list,
    create,
}arg_t;

typedef struct Args
{
    argtype type;
    std::string value;
}arg_s;

typedef struct dir
{
    std::string dir;
    std::string filename;
}dir_t;


std::string version = "1.0.0";

void printHelp();
void printVersion();
void mkFile(std::string file);

int main(int argc, char* argv[])
{
    std::vector<arg_s> argList;
    for(int i = 1; i < argc; i++)
    {
        std::string make = "-M";
        std::string make2 = "-m";
        std::string help = "-h";
        std::string version = "-v";
        std::string help2 = "--help";
        std::string version2 = "--version";
        std::string filename;
        if(argv[i][0] == '-' || (argv[i][0] == '-' && argv[i][1] == '-'))
        {
            if(argv[i] == make || argv[i] == make2)
            {
                filename.clear();
                filename.append(argv[i+1]);
                i++;
                argList.push_back({create, filename});
            }
            else if(argv[i] == help || argv[i] == help2)
            {
                printHelp();
                exit(0);
            }
            else if(argv[i] == version || argv[i] == version2)
            {
                printVersion();
                exit(0);
            }
            else
            {
                std::cout << "argument doesn't exist.";
                exit(1);
            }
        }
        else
        {
            filename.clear();
            filename.append(argv[i]);
            argList.push_back({create, filename});
        }
        
    }

    
    for(arg_s arg : argList)
    {
        if(arg.type == create)
        {
            mkFile(arg.value);
        }
    }
}
void mkFile(std::string file)
{
    std::filesystem::path path(file);
    if(path.has_parent_path())
    {
        std::filesystem::create_directories(path.parent_path());
    }
    std::ofstream cfile(file);
    cfile.close();
    
}

void printHelp()
{
    std::cout << "  -M {file} = make a file." << '\n';
    std::cout << "  -m {file} = make a file." << '\n';
    std::cout << "  -help > print help and exit." << '\n';
    std::cout << "  -h > print help and exit." << '\n';
    std::cout << "  -verion > print version and exit." << '\n';
    std::cout << "  -v > print version and exit." << '\n';
}

void printVersion()
{
    std::cout << version;
}