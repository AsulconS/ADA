#include <iostream>

int main()
{
    int n {};
    while(std::cin >> n)
    {
        int** M = new int*[n];
        for(int i = 0; i < n; ++i)
        {
            int* row = new int[n];
            for(int j = 0; j < n; ++j)
            {
                std::cin >> row[j];
            }
            M[i] = row;
        }

        // Delete temp matrix
        for(int i = 0; i < n; ++i)
        {
            delete M[i];
        }
        delete[] M;
    }

    return 0;
}
