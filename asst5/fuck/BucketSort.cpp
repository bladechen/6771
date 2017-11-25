#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <memory>

#include "BucketSort.h"

template<class Function>
void BucketSort::for_each(Function f)
{
    auto ncores = _concurrency;
    auto n = _total_numbers;
    auto each = n / ncores;
    auto nbonus = n % ncores;

    _threads.clear();

    bool flag = false;
    auto i_do = std::pair<size_t, size_t>();

    size_t first = 0;
    for (auto i = 0U; i < ncores; ++i)
    {
        size_t last = first + each + (i < nbonus ? 1 : 0);
        // std::cout << first << " " << last << std::endl;
        if (flag)
        {
            _threads.emplace_back(f, first, last);
        }
        else
        {
            flag = true;
            i_do.first = first;
            i_do.second = last;
        }
        first = last;
    }

    assert(_threads.size() + 1 == ncores);
    // doing part of jobs, because the spec says it should limit thread count.
    f(i_do.first, i_do.second);
    for (auto& thread : _threads)
        thread.join();
}


void BucketSort::count_sort(int exp)
{
    // uint32_t output
    static const int SIZE = 11 ;
    // static uint32_t *tmp_digit = new uint32_t[_total_numbers];
    std::atomic<int> count[SIZE];
    for (int i = 0; i < SIZE; ++ i)
    {
        count[i] = 0;
    }
    auto func = [&](size_t start, size_t end)
    {
        // Store count of occurrences in count[]
        int tmp_count[SIZE] = {0};
        for (size_t i = start; i < end; ++ i)
        {
            _tmp_digit[i] = get_digit(numbersToSort[i], exp);
            ++ tmp_count[static_cast<int>(_tmp_digit[i])];
        }
        for (int i = 0; i < SIZE; ++ i)
        {
            count[i] += tmp_count[i];
        }
    };
    for_each(func);

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (int i = 1; i < SIZE; ++ i)
        count[i] += count[i - 1];

    // Build the output array
    std::atomic<char> cur_count_idx {SIZE};
    auto func1 = [&](size_t nouse1, size_t nouse2)
    {
        (void)nouse1;
        (void)nouse2;
        while (1)
        {
            if (cur_count_idx < 0)
            {
                break;
            }
            char my_idx = cur_count_idx --;
            if (my_idx < 0)
            {
                break;
            }
            int local_count = count[static_cast<int>(my_idx)]; // caching line invalidation is high overhead

            for (int i = _total_numbers - 1; i >= 0; -- i)
            {
                if (_tmp_digit[i] == my_idx)
                {
                    _output[-- local_count]= numbersToSort[i];
                }
            }
        }
    };
    for_each(func1);
    std::swap(numbersToSort, _output);
}

void BucketSort::sort(unsigned int numCores)
{
    _total_numbers = numbersToSort.size();
    if (_total_numbers == 0)
    {
        return;
    }
    _concurrency = numCores;
    _threads.reserve(_concurrency);
    _output.resize(_total_numbers);
    _tmp_digit = new char[_total_numbers];
    _max_digit = 10; // 2^32 has 10 digits
    for (int exp = 1; exp <= _max_digit; ++ exp)
    {
        count_sort(exp);
    }
    delete [] _tmp_digit;
}
