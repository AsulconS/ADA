#include <iostream>

struct Tuple2
{
    int a;
    int b;
};

Tuple2 kadane(int* data, int size)
{
    Tuple2 globalBounds {0, 0};
    Tuple2 currentBounds {0, 0};
    int globalMax {data[0]};
    int currentMax {data[0]};

    for(int i = 1; i < size - 1; ++i)
    {
        if(data[i] > (currentMax + data[i]))
        {
            currentMax = data[i];
            currentBounds.a = currentBounds.b = i;
        }
        else
        {
            currentMax = currentMax + data[i];
            currentBounds.b = i;
        }

        if(currentMax > globalMax)
        {
            globalMax = currentMax;
            globalBounds = currentBounds;
        }
    }

    return globalBounds;
}

int main()
{
    int* A = new int[4] {-2, 3, 2, -1};
    Tuple2 bounds = kadane(A, 4);

    std::cout << bounds.a << ' ' << bounds.b << std::endl;

    return 0;
}
