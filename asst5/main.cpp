#include <iostream>
#include <random>
#include <mutex>
#include <thread>
#include "BucketSort.h"
void my_test()
{

    BucketSort pbs;

    pbs.numbersToSort.push_back(1);
    pbs.numbersToSort.push_back(8);
    pbs.numbersToSort.push_back(2);
    pbs.numbersToSort.push_back(0);
    pbs.sort(8);
    for (int i = 0; i < (int)(pbs.numbersToSort.size()); ++ i)
    {
        std::cout <<  pbs.numbersToSort[i] << std::endl;
    }

    pbs.numbersToSort.clear();

    pbs.numbersToSort.push_back(11);
    pbs.numbersToSort.push_back(1);
    pbs.sort(8);
    for (int i = 0; i < (int)(pbs.numbersToSort.size()); ++ i)
    {
        std::cout <<  pbs.numbersToSort[i] << std::endl;
    }

    pbs.numbersToSort.clear();

    pbs.numbersToSort.push_back(9);
    pbs.numbersToSort.push_back(0);
    pbs.numbersToSort.push_back(53);
    pbs.numbersToSort.push_back(5);
    pbs.numbersToSort.push_back(51);
    pbs.numbersToSort.push_back(2511);
    pbs.sort(8);
    for (int i = 0; i < (int)(pbs.numbersToSort.size()); ++ i)
    {
        std::cout <<  pbs.numbersToSort[i] << std::endl;
    }



}

int main() {
    my_test();
    unsigned int totalNumbers =	10000000;
    unsigned int printIndex =	259000;
    // use totalNumbers required as the seed for the random

    // number generator.

    std::mt19937 mt(totalNumbers);

    std::uniform_int_distribution<unsigned int> dist(1, std::numeric_limits<unsigned int>::max());
    // create a sort object

    BucketSort pbs;
    // insert random numbers into the sort object

    for (unsigned int i=0; i < totalNumbers; ++i) {

        pbs.numbersToSort.push_back(dist(mt));

    }

    // call sort giving the number of cores available.

    // const unsigned int numCores = std::thread::hardware_concurrency();

    const unsigned int numCores = 1;
    pbs.sort(numCores);

    std::cout << "number of cores used: " << numCores << std::endl;

    // print certain values from the buckets

    std::cout << "Demonstrating that all the numbers that start with 1 come first" << std::endl;

    std::cout << pbs.numbersToSort[0] << " " << pbs.numbersToSort[printIndex - 10000]

        << " " << pbs.numbersToSort[printIndex] << " " << pbs.numbersToSort[pbs.numbersToSort.size() - 1]

        << std::endl;

}
