#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H
#include <atomic>
#include <cassert>
#include <cstdint>
#include <thread>
#include <vector>

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

static const uint32_t decimal[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

struct BucketSort
{
    public:
        std::vector<unsigned int> numbersToSort;
        void sort(unsigned int numCores);

    private:

        template<class Function> void for_each(Function f);
        void count_sort(int exp);

        size_t _total_numbers;


        uint32_t _concurrency;
        // std::atomic<int> _mx; // maximum digit count;
        std::vector<std::thread> _threads;

        std::vector <uint32_t> _output; // output array


        char* _tmp_digit{nullptr};

        uint32_t _last_size{0};

        int _max_digit;

        // from stackoverflow
        // get  digits of n
        inline uint32_t get_digits(uint32_t n)
        {
            static uint32_t powers[10] = {
                0, 10, 100, 1000, 10000, 100000, 1000000,
                10000000, 100000000, 1000000000,
            };
            static unsigned maxdigits[33] = {
                1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5,
                5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10,
            };
            if (unlikely(!n)) // __builtin_clz(0) is undefined behaviour
            {
                return 1;
            }
            unsigned bits = 32 - __builtin_clz(n);
            unsigned digits = maxdigits[bits];
            if (unlikely(n < powers[digits - 1]))
            {
                -- digits;
            }
            return digits;
        }

        inline char get_digit(uint32_t number, int index)
        {
            int digit_count = get_digits(number);
            int tmp = index - (11 - digit_count);
            if (likely(tmp < 0))
            {
                return 0;
            }
            else
            {
                return 1 + (number / decimal[tmp] % 10);
            }
        }

};
#endif
