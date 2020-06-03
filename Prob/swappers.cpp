#include <iostream>

template <typename T>
void swap(T& v1, T& v2)
{
    T t = v1;
    v1 = v2;
    v2 = t;
}

int getSwaps(int* data, int size)
{
    int count {0};
    int j {size};
    while(j--)
    {
        for(int i = 0; i < j; ++i)
        {
            if(data[i] > data[i + 1])
            {
                swap(data[i], data[i + 1]);
                ++count;
            }
        }
    }
    return count;
}

int main()
{
    int tests {};
    std::cin >> tests;

    int* results = new int[tests];
    for(int i = 0; i < tests; ++i)
    {
        int l {};
        std::cin >> l;
        int* train = new int[l];
        for(int j = 0; j < l; ++j)
        {
            std::cin >> train[j];
        }
        results[i] = getSwaps(train, l);
        delete[] train;
    }
    for(int i = 0; i < tests; ++i)
    {
        std::cout << "Optimal train swapping takes " << results[i] << " swaps.\n";
    }
    std::cout << std::flush;

    delete[] results;

    return 0;
}
