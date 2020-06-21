#include <chrono>
#include <random>
#include <cstdlib>

#include <string>
#include <fstream>
#include <iostream>


/********************************************************************************
 * Utility functions                                                            *
 ********************************************************************************/
template <typename T>
void swap(T& v1, T& v2)
{
    T temp = v1;
    v1 = v2;
    v2 = temp;
}

void genArrays(int** arrays, int n, int size)
{
    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_int_distribution<int> dist(0, (1 << 30));

    for(int j = 0; j < size; ++j)
    {
        int val = dist(mt);
        for(int i = 0; i < n; ++i)
        {
            arrays[i][j] = val;
        }
    }
}

void printArray(int* data, int size)
{
    for(int i = 0; i < size; ++i)
    {
        std::cout << data[i] << ' ';
    }
    std::cout << std::endl;
}
/********************************************************************************/


/********************************************************************************
 * Max and Quicksort Function implementation                                    *
 ********************************************************************************/
template <typename T>
T getMax(T* data, int size, int& timesComp)
{
    timesComp = 0;

    T globalMax = data[0];
    for(int i = 1; i < size; ++i)
    {
        if(data[i] > globalMax)
        {
            globalMax = data[i];
            ++timesComp;
        }
    }
    return globalMax;
}

template <typename T>
int partition(T* data, int p, int r, int& timesComp)
{
    T pivot = data[r];
    int i = p - 1;
    for(int j = p; j < r; ++j)
    {
        if(data[j] <= pivot)
        {
            ++i;
            swap(data[i], data[j]);
            ++timesComp;
        }
    }
    swap(data[i + 1], data[r]);
    return i + 1;
}

template <typename T>
void quickSortInternal(T* data, int p, int r, int& timesComp)
{
    if(p < r)
    {
        int q = partition(data, p, r, timesComp);
        quickSortInternal(data, p, q - 1, timesComp);
        quickSortInternal(data, q + 1, r, timesComp);
    }
}

template <typename T>
void quickSort(T* data, int size, int& timesComp)
{
    timesComp = 0;
    quickSortInternal(data, 0, size - 1, timesComp);
}
/********************************************************************************/


/********************************************************************************
 * Permormance test functions                                                   *
 ********************************************************************************/
void maxPerformanceTest(int size, float& avg)
{
    int* A {nullptr};

    avg = 0;
    int timesComp;
    for(int i = 0; i < 200; ++i)
    {
        A = new int[size];
        genArrays(&A, 1, size);
        getMax(A, size, timesComp);
        avg += timesComp;
        delete[] A;
    }
    avg /= 200;

    std::cout << "\tMax function average: " << avg << " times" << std::endl;
}

void quickPerformanceTest(int size, float& avg)
{
    int* A {nullptr};

    avg = 0;
    int timesComp;
    for(int i = 0; i < 200; ++i)
    {
        A = new int[size];
        genArrays(&A, 1, size);
        quickSort(A, size, timesComp);
        avg += timesComp;
        delete[] A;
    }
    avg /= 200;

    std::cout << "\tQuicksort function average: " << avg << " times" << std::endl;
}
/********************************************************************************/


/********************************************************************************
 * Main function                                                                *
 ********************************************************************************/
int main()
{
    int numTests {};
    std::cout << "Insert the n of tests (Stepped by its double):\n";
    std::cout << "\ti.e. 13 is for testing n from 2^8 to 2^20\n\t";
    std::cin  >> numTests;
    std::cout << std::endl;

    int sel {};
    std::cout << "Select mode: 1. Max Algorithm, 2. Quicksort:\n\t";
    std::cin  >> sel;
    std::cout << std::endl;

    if(numTests < 1)
    {
        return -1;
    }

    float* results = new float[numTests];

    int rightLimit {256 << (numTests - 1)};

    std::cout << "Performance test started!\n" << std::endl;
    for(int i = 256, j = 0; i <= rightLimit; i <<= 1, ++j)
    {
        std::cout << "Data size: " << i << ':' << std::endl;
        switch(sel)
        {
            case 1:
                maxPerformanceTest(i, results[j]);
                break;

            case 2:
                quickPerformanceTest(i, results[j]);
                break;

            default:
                break;
        }
    }

    std::string resultsFilename;
    switch(sel)
    {
        case 1:
            {
                resultsFilename = "./results/resultsE6M_";
            }
            break;

        case 2:
            {
                resultsFilename = "./results/resultsE6Q_";
            }
            break;

        default:
            {
                resultsFilename = "./results/resultsE6_";
            }
            break;
    }
    resultsFilename += std::to_string(numTests) + ".dt";

    std::ofstream of {};
    of.open(resultsFilename);
    for(int i = 256, j = 0; i <= rightLimit; i <<= 1, ++j)
    {
        of << i << ' ' << results[j] << '\n';
        of.flush();
    }
    of.close();

    delete[] results;
    return 0;
}
/********************************************************************************/
