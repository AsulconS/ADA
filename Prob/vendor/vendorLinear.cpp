#include <iostream>

struct Segment
{
    int a;
    int b;
    int sum;
};

Segment kadane(int* data, int size)
{
    Segment globalBounds {0, 0, 0};
    Segment currentBounds {0, 0, 0};
    int globalMax {data[0]};
    int currentMax {data[0]};

    for(int i = 1; i < size; ++i)
    {
        if(data[i] > (currentMax + data[i]))
        {
            currentMax = data[i];
            currentBounds.a = currentBounds.b = i;
        }
        else
        {
            currentMax += data[i];
            currentBounds.b = i;
        }

        if(currentMax >= globalMax)
        {
            globalMax = currentMax;
            globalBounds = currentBounds;
        }
    }

    globalBounds.sum = globalMax;
    return globalBounds;
}

int main()
{
    int r {};
    std::cin >> r;

    Segment* ans = new Segment[r];

    int c {};
    for(int i = 0; i < r; ++i)
    {
        std::cin >> c; --c;
        int* rute = new int[c];
        for(int j = 0; j < c; ++j)
        {
            std::cin >> rute[j];
        }
        ans[i] = kadane(rute, c);

        delete[] rute;
    }

    for(int i = 0; i < r; ++i)
    {
        if(ans[i].sum > 0)
        {
            std::cout << "La mejor parte de la ruta " << (i + 1) << " es entre las calles " << (ans[i].a + 1) << " y " << (ans[i].b + 2) << std::endl;
        }
        else
        {
            std::cout << "La ruta " << (i + 1) << " no tiene calles interesantes" << std::endl;
        }
    }

    delete[] ans;
    return 0;
}
