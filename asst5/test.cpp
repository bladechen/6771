

#include <vector>


struct BucketSort {



    // vector of numbers

    std::vector<unsigned int> numbersToSort;


    void sort(unsigned int numCores);

};



#include <algorithm>

#include <cmath>


bool aLessB(const unsigned int& x, const unsigned int& y, unsigned int pow) {



        if (x == y) return false; // if the two numbers are the same then one is not less than the other



        unsigned int a = x;

        unsigned int b = y;



        // work out the digit we are currently comparing on.

        if (pow == 0) {

                while (a / 10 > 0) {

                        a = a / 10;

                }

                while (b / 10 > 0) {

                        b = b / 10;

                }

        } else {

            while (a / 10 >= (unsigned int) std::round(std::pow(10,pow))) {

                        a = a / 10;

                }

                while (b / 10 >= (unsigned int) std::round(std::pow(10,pow))) {

                        b = b / 10;

                }

        }


        if (a == b)

                return aLessB(x,y,pow + 1);  // recurse if this digit is the same

        else

                return a < b;

}


// TODO: replace this with a parallel version.

void BucketSort::sort(unsigned int numCores) {

        std::sort(numbersToSort.begin(),numbersToSort.end(), [](const unsigned int& x, const unsigned int& y){

                return aLessB(x,y,0);

        } );

}
#include <iostream>

#include <random>

#include <thread>



int main() {



    unsigned int totalNumbers =    500000;

    unsigned int printIndex =    259000;



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

        const unsigned int numCores = std::thread::hardware_concurrency();

        pbs.sort(numCores);


        std::cout << "number of cores used: " << numCores << std::endl;



    // print certain values from the buckets

    std::cout << "Demonstrating that all the numbers that start with 1 come first" << std::endl;

    std::cout << pbs.numbersToSort[0] << " " << pbs.numbersToSort[printIndex - 10000]

        << " " << pbs.numbersToSort[printIndex] << " " << pbs.numbersToSort[pbs.numbersToSort.size() - 1]

        << std::endl;



}
