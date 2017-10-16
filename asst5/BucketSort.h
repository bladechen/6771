#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H
#include <vector>
#include <cassert>
#include <atomic>
#include <cstdint>
#include <thread>
struct BucketSort
{
    public:
        std::vector<unsigned int> numbersToSort;
        void sort(unsigned int numCores);

    private:

        template<class Function> void for_each(Function f);
        void count_sort(int exp);

        struct Number
        {
            char digit[12];
            int count;
        };

        size_t _total_numbers;
        std::vector<Number> _tmp_numbers;

        // int getMaxDigitCount();

        void int_to_digits();
        void digits_to_int();
        uint32_t _concurrency;
        std::atomic<uint32_t> _mx; // maximum digit count;
        std::vector<std::thread> _threads;
};
#endif
