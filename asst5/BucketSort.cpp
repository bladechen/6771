#include "BucketSort.h"
#include <mutex>
#include <memory>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

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
    // doing part of jobs, because the f**k spec says it should limit thread count.
    f(i_do.first, i_do.second);
    for (auto& thread : _threads)
        thread.join();
}

void BucketSort::int_to_digits()
{
    auto func = [&](size_t start, size_t end)
    {

        size_t len = end - start;
        Number* local_tmp = new Number[len];
        memset(local_tmp, 0, sizeof(Number) * len);
        for (size_t i = 0; i < len; ++ i)
        {
            char buffer[16] = {0};
            uint32_t local_num = numbersToSort[i];
            local_tmp[i].original = local_num;
            int tmp_len = snprintf (buffer, 15, "%u", local_num);
            for (int j = 0 ; j < tmp_len; ++ j)
            {
                buffer[j] = buffer [j] - '0' + 1;
            }
            for (int j = 0; j < 6; j ++)
            {
                local_tmp[i].digit[j] = buffer[j << 1] * 11 + buffer[(j << 1) + 1];
            }
            // _tmp_numbers[i].original = original;
        }

        memcpy(_tmp_numbers + start, local_tmp, sizeof (Number) * len);
        delete [] local_tmp;
    };
    for_each(func);
}

void BucketSort::count_sort(int exp)
{
    // std::vector <Number> output; // output array
    // output.resize(_total_numbers);
    // uint32_t output
    static const int SIZE = 11 * 11 ;
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
            ++ tmp_count[static_cast<size_t>(_tmp_numbers[i].digit[exp])];
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
    std::mutex m;
    std::atomic<char> cur_count_idx {SIZE};
    // int index = static_cast<int>(_total_numbers - 1);
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
            int local_count = count[static_cast<int>(my_idx)]; // caching line invalid is high overhead

            // Number* local_tmp = new Number[local_count];
            for (int i = _total_numbers - 1; i >= 0; -- i)
            {
                char tmp = (_tmp_numbers[i].digit[exp]);
                if (tmp == my_idx)
                {
                    _tmp_output[-- local_count]= _tmp_numbers[i];
                }
            }
        }
    };
    for_each(func1);
    // contains sorted numbers according to current digit
    // _tmp_numbers = std::swap(_tmp_output);
    auto tmp_ptr = _tmp_numbers;
    _tmp_numbers = _tmp_output;
    _tmp_output = tmp_ptr;
}

void BucketSort::sort(unsigned int numCores)
{
    _total_numbers = numbersToSort.size();
    if (_total_numbers == 0)
    {
        return;
    }
    if (_last_size < _total_numbers)
    {
        delete[] _tmp_output;
        delete[] _tmp_numbers;
        _tmp_output = new Number[_total_numbers];
        _tmp_numbers = new Number[_total_numbers]; // TODO no malloc n
        _last_size = _total_numbers;
    }
    _mx = 6;
    _concurrency = numCores;
    _threads.reserve(_concurrency);
    int_to_digits();
    for (int exp = static_cast<int>(_mx - 1); exp >= 0; --exp)
    {
        count_sort(exp);
    }
    digits_to_int();
}

void BucketSort::digits_to_int()
{
    for (size_t i = 0; i < _total_numbers; ++ i)
    {
        numbersToSort[i] = _tmp_numbers[i].original;
    }
}
