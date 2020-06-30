#include <cstdlib>
#include <iostream>

#define MX 2000000000

int main()
{
    int n {8000};
    for(int i = 0; i < n; ++i)
    {
        std::cout << n << ' ';
        for(int j = 0; j < n; ++j)
        {
            std::cout << (rand() % MX) << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
