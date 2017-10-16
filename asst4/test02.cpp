#include <algorithm>
#include <iostream>
#include <iterator>

#include "btree.h"

void foo(const btree<int> &b) {
    std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main(void) {
    btree<int> b;

    b.insert(1);
    b.insert(10);
    b.insert(3);
    b.insert(4);

    for(btree<int>::const_iterator iter = b.cbegin(); iter != b.cend(); ++iter)
        std::cout << *iter << std::endl;
    // for(const)
    //     std::cout << *iter << std::endl;


    for(btree<int>::reverse_iterator iter = b.rbegin(); iter != b.rend(); ++iter)
        std::cout << *iter << std::endl;

    foo(b);



    btree<int> bb(2);

    bb.insert(1);
    bb.insert(2);
    bb.insert(3);
    bb.insert(4);
    bb.insert(5);
    bb.insert(6);
    bb.insert(7);
    bb.insert(9);
    bb.insert(10);
    bb.insert(20);
    bb.insert(21);
    bb.insert(24);
    bb.insert(100);

    for(btree<int>::iterator iter = bb.begin(); iter != bb.end(); ++iter)
    {
        (*iter) ++;
        std::cout << *iter << std::endl;
    }

    foo(bb);


    return 0;
}
