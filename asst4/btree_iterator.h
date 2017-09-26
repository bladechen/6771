#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

#include "btree.h"
/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)


template <typename T>
class Identity
{
    public:
    using type = T;
};

template <typename T,template <typename U> class Constness> class btree_iterator;
template <typename T,template <typename U> class Constness>
bool operator==(const btree_iterator<T, Constness>& l, const btree_iterator<T, Constness>& r);

template <typename T,template <typename U> class Constness>
bool operator!=(const btree_iterator<T, Constness>& l, const btree_iterator<T, Constness>& r);

template <typename T,
          template <typename U> class Constness = Identity>
class btree_iterator
{
    using IT = typename Constness<T>::type;
public:
    using iterator_category = std::bidirectional_iterator_tag iterator_category;
    using difference_type = std::ptrdiff_t difference_type;
    using value_type = T;
    using pointer = IT*;
    using reference = IT&;

    btree_iterator(Element* elem) : _index{elem} {};
    btree_iterator(const btree_iterator& it);

    // // TODO
    // reference operator*();
    // pointer   operator->();

    reference operator*() const;
    pointer   operator->() const;
    btree_iterator& operator--();
    btree_iterator  operator--(int);
    btree_iterator& operator++();
    btree_iterator  operator++(int);

    operator btree_iterator<T, std::add_const>();
    // TODO non-const == const?
    friend  bool operator ==<>(const btree_iterator<T, Constness>& l, const btree_iterator<T, Constness>& r);
    friend  bool operator !=<>(const btree_iterator<T, Constness>& l, const btree_iterator<T, Constness>& r);
private:
    typename std::vector<Element>::iterator _it;
};

// FIXME
template <typename T,template <typename U> class Constness>
btree_iterator<T, Constness>::btree_iterator(const btree_iterator<T, Constness>& it)
{
    _it = it->_it;
}

template <typename T,template <typename U> class Constness>
reference btree_iterator<T, Constness>::operator*() const
{
    return _it->_val;
}

template <typename T,template <typename U> class Constness>
pointer   btree_iterator<T, Constness>::operator->() const
{
    return &(*this);
}

template <typename T,template <typename U> class Constness>
btree_iterator& btree_iterator<T, Constness>::operator--()
{
}

template <typename T,template <typename U> class Constness>
btree_iterator  btree_iterator<T, Constness>::operator--(int)
{
    btree_iterator ret = *this;
    -- (*this);
    return ret;
}

template <typename T,template <typename U> class Constness>
btree_iterator& btree_iterator<T, Constness>::operator++()
{
    assert(_index != nullptr && _index->marker != HEAD_ELEMENT);

    for

    return *this;
    // if (_index->)
}

template <typename T,template <typename U> class Constness>
btree_iterator btree_iterator<T, Constness>::operator++(int)
{
    btree_iterator ret = *this;
    ++ (*this);
    return ret;
}

template <typename T,template <typename U> class Constness>
operator btree_iterator<T, Constness>::btree_iterator<T, std::add_const>()
{
    return btree_iterator<T, std::add_const>(*this);
}

template <typename T,template <typename U> class Constness>
bool operator==(const btree_iterator<T, Constness>& l, const btree_iterator<T, Constness>& r)
{
    return l->_it == r->_it;
}

template <typename T,template <typename U> class Constness>
bool operator!=(const btree_iterator<T, Constness>& l, const btree_iterator<T, Constness>& r)
{
    return !(l == r);
}
#endif
