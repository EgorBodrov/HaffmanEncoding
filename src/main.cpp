#include "haffman.h"

int main()
{
    char name[] = "input.txt";
    std::string a = ReadData(name);
    
    Start(a);

    return 0;
}
