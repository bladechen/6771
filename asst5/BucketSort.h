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
        virtual ~BucketSort()
        {
            delete[] _tmp_numbers;
            delete[] _tmp_output;
        }

    private:

        template<class Function> void for_each(Function f);
        void count_sort(int exp);

        struct Number
        {
            char digit[8];
            int count;
            uint32_t original;
        };

        size_t _total_numbers;

        // std::vector<Number> _tmp_numbers;

        // int getMaxDigitCount();

        void int_to_digits();
        void digits_to_int();
        uint32_t _concurrency;
        std::atomic<int> _mx; // maximum digit count;
        std::vector<std::thread> _threads;
        Number* _tmp_output{nullptr};
        Number* _tmp_numbers{nullptr};

        uint32_t _last_size{0};
};
#endif
