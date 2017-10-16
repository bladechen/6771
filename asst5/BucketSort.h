#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H
#include <vector>
struct BucketSort {
    std::vector<unsigned int> numbersToSort;
    void sort(unsigned int numCores);
};
#endif
