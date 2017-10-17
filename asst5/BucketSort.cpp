#include "BucketSort.h"
#include <mutex>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

uint32_t get_digits(uint32_t n) {
    static uint32_t powers[10] = {
        0, 10, 100, 1000, 10000, 100000, 1000000,
        10000000, 100000000, 1000000000,
    };
    static uint32_t maxdigits[33] = {
        1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5,
        5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10,
    };
    uint32_t bits = sizeof(n) * 8 - __builtin_clz(n);
    assert(bits <= 32);
    uint32_t digits = maxdigits[bits];
    if (n < powers[digits - 1]) {
        -- digits;
    }
    return digits;
}

template<class Function>
void BucketSort::for_each(Function f)
{
    auto ncores = _concurrency;
    auto n = numbersToSort.size();
    auto each = n / ncores;
    auto nbonus = n % ncores;

    _threads.clear();

    size_t first = 0;
    for (auto i = 0U; i < ncores; ++i) {
        auto last = first + each + (i < nbonus ? 1 : 0);
        _threads.emplace_back(f, first, last);
        first = last;
    }

    assert(first == n);
    for (auto& thread : _threads)
        thread.join();
}

void BucketSort::int_to_digits()
{
    _threads.clear();
    _tmp_numbers.clear();
    _tmp_numbers.resize(_total_numbers);
    auto func = [&](size_t start, size_t end)
    {
        uint32_t mx = 0;
        char buffer[64];
        for (size_t i = start; i < end; ++ i)
        {
            mx = std::max(get_digits(numbersToSort[i]), mx);
            int len = std::snprintf(buffer, sizeof(buffer), "%u", numbersToSort[i]);
            assert(len > 0);
            memset(&_tmp_numbers[i], 0, sizeof(Number));
            for (int j = 0; j < len; ++ j)
            {
                _tmp_numbers[i].digit[j] = buffer[j] - '0' + 1;
            }
            _tmp_numbers[i].count = len;
        }
        uint32_t prev_value = _mx;
        while(prev_value < mx &&
              !_mx.compare_exchange_weak(prev_value, mx))
            ;
    };
    for_each(func);
}

void BucketSort::count_sort(int exp)
{
    std::vector <Number> output; // output array
    output.resize(_total_numbers);
    std::atomic<int> count[11];
    for (int i = 0; i < 11; ++ i)
    {
        count[i] = 0;
    }
    auto func = [&](size_t start, size_t end)
    {
        // Store count of occurrences in count[]
        int tmp_count[11] = {0};
        for (size_t i = start; i < end; ++ i)
        {
            ++ tmp_count[static_cast<size_t>(_tmp_numbers[i].digit[exp])];
        }
        for (int i = 0; i < 11; ++ i)
        {
            count[i] += tmp_count[i];
        }
    };
    for_each(func);

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (int i = 1; i < 11; ++ i)
        count[i] += count[i - 1];

    // Build the output array
    std::mutex m;
    int index = static_cast<int>(_total_numbers - 1);
    auto func1 = [&](size_t nouse1, size_t nouse2)
    {
        (void)nouse1;
        (void)nouse2;
        while (1)
        {
            std::lock_guard<std::mutex> l{m};
            if (index >= 0)
            {
                output[-- count[ static_cast<size_t>(_tmp_numbers[index].digit[exp])] ] = _tmp_numbers[index];
                -- index;
            }
            else
            {
                break;
            }
        }
    };
    for_each(func1);
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    assert(_tmp_numbers.size() == output.size());
    assert(index == -1);
    _tmp_numbers = std::move(output);
}

void BucketSort::sort(unsigned int numCores)
{
    _total_numbers = numbersToSort.size();
    _mx = 0;
    _concurrency = numCores;
    // _threads.reserve(_concurrency);
    int_to_digits();
    for (int exp = static_cast<int>(_mx - 1); exp >= 0; --exp)
    {
        count_sort(exp);
    }

    digits_to_int();

}
void BucketSort::digits_to_int()
{
    numbersToSort.resize(_total_numbers);
    auto func = [&](size_t start, size_t end)
    {
        // std::string ss;
        for (size_t i = start; i < end; ++ i)
        {
            uint32_t tmp_num = 0;
            // ss.clear();
            // std::cout << _tmp_numbers[i].count << std::endl;
            for (int j = 0; j < _tmp_numbers[i].count; ++ j)
            {
                tmp_num = tmp_num * 10 + _tmp_numbers[i].digit[j] - 1;

            }
            numbersToSort[i] = tmp_num;
        }
    };
    for_each(func);
}