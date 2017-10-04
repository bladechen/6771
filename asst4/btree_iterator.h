#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H
#include <iterator>
#include "btree.h"

template <typename T>
class Identity
{
    public:
    using type = T;
};

template <typename T> class btree;
template <typename T,template <typename U> class Constness> class btree_iterator;

// comparing const iterator with non-const iterator
template <typename T1,template <typename U> class Constness0, template <typename U1> class Constness1>
bool operator==(const btree_iterator<T1, Constness0>& l, const btree_iterator<T1, Constness1>& r);

template <typename T1,template <typename U> class Constness0, template <typename U1> class Constness1>
bool operator!=(const btree_iterator<T1, Constness0>& l, const btree_iterator<T1, Constness1>& r);

template <typename T, template <typename U> class Constness = Identity>
class btree_iterator
{

    using IT = typename Constness<T>::type;

    template <typename T1, template <typename U1> class Constness1>
    struct vector_iterator
    {
        using type = typename std::vector<typename btree<T1>::Element>::iterator;
    };

    template <typename T1, template <typename U1> class Constness1>
    struct btree_t
    {
        using type = btree<T>*;
    };

    template <typename T1>
    struct btree_t<T1,  std::add_const>
    {
        using type = const btree<T>*;
    };

    using vector_iterator_type = typename vector_iterator<T, Constness>::type;
    using btree_type = typename btree_t<T, Constness>::type;
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = IT*;
    using reference = IT&;

    btree_iterator(btree_type tree, const vector_iterator_type& it)
        : _it{it},  _owner {tree} {};
    btree_iterator(const btree_iterator& it);
    btree_iterator(){};

    reference operator*() const;
    pointer   operator->() const;
    btree_iterator& operator--();
    btree_iterator  operator--(int);
    btree_iterator& operator++();
    btree_iterator  operator++(int);

    // only make function for class while its Constness is Identity
    template <typename U = T, typename = typename
        std::enable_if<std::is_same<Constness<U>, Identity<U> >::value && std::is_same<U, T>::value>::type>
    operator btree_iterator<T, std::add_const>()
    {
        return btree_iterator<T, std::add_const>(_owner, _it);
    }

    template <typename T1,template <typename U> class Constness0, template <typename U1> class Constness1>
    friend  bool operator==(const btree_iterator<T1, Constness0>& l, const btree_iterator<T1, Constness1>& r);

    template <typename T1,template <typename U> class Constness0, template <typename U1> class Constness1>
    friend  bool operator!=(const btree_iterator<T1, Constness0>& l, const btree_iterator<T1, Constness1>& r);

private:
    vector_iterator_type _it;
    btree_type _owner{nullptr};
};

template <typename T,template <typename U> class Constness>
btree_iterator<T, Constness>::btree_iterator(const btree_iterator<T, Constness>& it): _it{it._it}, _owner{it._owner}
{
}

template <typename T,template <typename U> class Constness>
typename btree_iterator<T, Constness>::reference btree_iterator<T, Constness>::operator*() const
{
    return _it->_val;
}

template <typename T,template <typename U> class Constness>
typename btree_iterator<T, Constness>::pointer btree_iterator<T, Constness>::operator->() const
{
    return &(*this);
}

template <typename T,template <typename U> class Constness>
btree_iterator<T, Constness>& btree_iterator<T, Constness>::operator--()
{
    _it = _owner->backward_iter(_it);
    return *this;
}

template <typename T,template <typename U> class Constness>
btree_iterator<T, Constness>  btree_iterator<T, Constness>::operator--(int)
{
    btree_iterator ret = *this;
    -- (*this);
    return ret;
}

template <typename T,template <typename U> class Constness>
btree_iterator<T, Constness>& btree_iterator<T, Constness>::operator++()
{
    _it = _owner->forward_iter(_it);
    return *this;
}

template <typename T,template <typename U> class Constness>
btree_iterator<T, Constness> btree_iterator<T, Constness>::operator++(int)
{
    btree_iterator ret = *this;
    ++ (*this);
    return ret;
}

template <typename T1, template <typename U> class Constness0, template <typename U1> class Constness1>
bool operator==(const btree_iterator<T1, Constness0>& l, const btree_iterator<T1, Constness1>& r)
{
    return (l._owner == r._owner && l._it == r._it);
}

template <typename T1, template <typename U> class Constness0, template <typename U1> class Constness1>
bool operator!=(const btree_iterator<T1, Constness0>& l, const btree_iterator<T1, Constness1>& r)
{
    return !(l == r);
}
#endif
