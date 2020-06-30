#include <iostream>

template <typename T>
void swap(T& v1, T& v2)
{
    T temp = v1;
    v1 = v2;
    v2 = temp;
}

template <typename T>
int partition(T* data, int p, int r)
{
    T& pivot = data[r];
    int i = p - 1;
    for(int j = p; j < r; ++j)
    {
        if(data[j] < pivot)
        {
            ++i;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[r]);
    return i + 1;
}

template <typename T>
T findMedian(T* data, int n)
{
    int p {0};
    int r {n - 1};
    int k = n / 2;
    int q {};
    while(true)
    {
        q = partition(data, p, r);
        if(q == k)
        {
            return data[k];
        }

        if(q < k)
        {
            p = q + 1;
        }
        else
        {
            r = q - 1;
        }
    }
}

int main()
{
    int n {};
    std::cin >> n;
    int* data = new int[n];

    do
    {
        for(int i = 0; i < n; ++i)
        {
            std::cin >> data[i];
        }

        int median = findMedian(data, n);
    }
    while(std::cin >> n);

    delete data;
    return 0;
}
