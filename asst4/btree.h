/**
 * TODO add noexcept
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node
 * that stores m client elements partition the tree
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cassert>
#include <cstddef>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <queue>

#include "btree_iterator.h"

// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)
template <typename T> class btree;

template <typename T>
std::ostream& operator<<(std::ostream& os, const btree<T>& tree);



template <typename T>
class btree
{
        struct Element;
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using iterator = btree_iterator<T>;
        using const_iterator = btree_iterator<T, std::add_const>;
        using reverse_iterator = typename std::reverse_iterator<iterator>;//decltype(std::make_reverse_iterator(it));
        using const_reverse_iterator = typename std::reverse_iterator<const_iterator>;

        friend iterator;
        friend const_iterator;

        /**
         * Constructs an empty btree.  Note that
         * the elements stored in your btree must
         * have a well-defined zero-arg constructor,
         * copy constructor, operator=, and destructor.
         * The elements must also know how to order themselves
         * relative to each other by implementing operator<
         * and operator==. (These are already implemented on
         * behalf of all built-ins: ints, doubles, strings, etc.)
         *
         * @param maxNodeElems the maximum number of elements
         *        that can be stored in each B-Tree node
         */
        btree(size_t maxNodeElems = 40);

        /**
         * The copy constructor and  assignment operator.
         * They allow us to pass around B-Trees by value.
         * Although these operations are likely to be expensive
         * they make for an interesting programming exercise.
         * Implement these operations using value semantics and
         * make sure they do not leak memory.
         */

        /**
         * Copy constructor
         * Creates a new B-Tree as a copy of original.
         *
         * @param original a const lvalue reference to a B-Tree object
         */
        btree(const btree<T>& original);

        /**
         * Move constructor
         * Creates a new B-Tree by "stealing" from original.
         *
         * @param original an rvalue reference to a B-Tree object
         */
        btree(btree<T>&& original) noexcept;


        /**
         * Copy assignment
         * Replaces the contents of this object with a copy of rhs.
         *
         * @param rhs a const lvalue reference to a B-Tree object
         */
        btree<T>& operator=(const btree<T>& rhs);

        /**
         * Move assignment
         * Replaces the contents of this object with the "stolen"
         * contents of original.
         *
         * @param rhs a const reference to a B-Tree object
         */
        btree<T>& operator=(btree<T>&& rhs) noexcept;

        /**
         * Puts a breadth-first traversal of the B-Tree onto the output
         * stream os. Elements must, in turn, support the output operator.
         * Elements are separated by space. Should not output any newlines.
         *
         * @param os a reference to a C++ output stream
         * @param tree a const reference to a B-Tree object
         * @return a reference to os
         */
        friend std::ostream& operator<< <> (std::ostream& os, const btree<T>& tree);

        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator begin() const {return cbegin();};
        const_iterator end() const {return cend();};

        reverse_iterator rbegin() {return reverse_iterator{end()};};
        reverse_iterator rend() {return reverse_iterator{begin()};};
        const_reverse_iterator crbegin() const {return const_reverse_iterator{cend()};};
        const_reverse_iterator crend() const {return const_reverse_iterator{cbegin()};};
        const_reverse_iterator rbegin() const {return crbegin();};
        const_reverse_iterator rend() const {return crend();};

        /**
         * Returns an iterator to the matching element, or whatever
         * the non-const end() returns if the element could
         * not be found.
         *
         * @param elem the client element we are trying to match.  The elem,
         *        if an instance of a true class, relies on the operator< and
         *        and operator== methods to compare elem to elements already
         *        in the btree.  You must ensure that your class implements
         *        these things, else code making use of btree<T>::find will
         *        not compile.
         * @return an iterator to the matching element, or whatever the
         *         non-const end() returns if no such match was ever found.
         */
        iterator find(const T& elem);

        /**
         * Identical in functionality to the non-const version of find,
         * save the fact that what's pointed to by the returned iterator
         * is deemed as const and immutable.
         *
         * @param elem the client element we are trying to match.
         * @return an iterator to the matching element, or whatever the
         *         const end() returns if no such match was ever found.
         */
        const_iterator find(const T& elem) const;

        /**
         * Operation which inserts the specified element
         * into the btree if a matching element isn't already
         * present.  In the event where the element truly needs
         * to be inserted, the size of the btree is effectively
         * increases by one, and the pair that gets returned contains
         * an iterator to the inserted element and true in its first and
         * second fields.
         *
         * If a matching element already exists in the btree, nothing
         * is added at all, and the size of the btree stays the same.  The
         * returned pair still returns an iterator to the matching element, but
         * the second field of the returned pair will store false.  This
         * second value can be checked to after an insertion to decide whether
         * or not the btree got bigger.
         *
         * The insert method makes use of T's zero-arg constructor and
         * operator= method, and if these things aren't available,
         * then the call to btree<T>::insert will not compile.  The implementation
         * also makes use of the class's operator== and operator< as well.
         *
         * @param elem the element to be inserted.
         * @return a pair whose first field is an iterator positioned at
         *         the matching element in the btree, and whose second field
         *         stores true if and only if the element needed to be added
         *         because no matching element was there prior to the insert call.
         */
        std::pair<iterator, bool> insert(const T& elem);

        /**
         * Disposes of all internal resources, which includes
         * the disposal of any client objects previously
         * inserted using the insert operation.
         * Check that your implementation does not leak memory!
         */
        ~btree() ;

    private:
        struct Node;
        struct Element;

        enum ELEMENT_MARKER_E
        {
            DUMMY_EMELEMT = 1,
            NORMAL_ELEMENT = 3,
        };

        struct Element
        {
            Element(enum ELEMENT_MARKER_E m, Node* owner): _marker{m}, _owner{owner}{};
            Element(const T& t,
                    Node* owner, Node* left, Node* right, enum ELEMENT_MARKER_E m = NORMAL_ELEMENT)
                : _val{t}, _marker{m}, _left{left},_right{right}, _owner{owner}{};
            virtual ~Element()
            {
                if (_right != nullptr)
                {
                    delete _right;
                    _right = nullptr;
                }
                if (_right != nullptr)
                {
                    delete _right;
                    _right = nullptr;
                }
            }

            T _val;
            enum ELEMENT_MARKER_E _marker;
            // internal nodes only use _right
            Node* _left {nullptr};
            Node* _right{nullptr};
            Node* _owner{nullptr};

            bool operator< (const Element& right)
            {
                if (_marker == right._marker && _marker == NORMAL_ELEMENT)
                {
                    return _val < right._val;
                }
                else
                {
                    return _marker < right._marker;
                }
            }

            bool operator== (const Element& right)
            {
                if (_marker == right._marker && _marker != NORMAL_ELEMENT)
                {
                    return true;
                }
                return _val == right._val;
            }
        };

        struct Node
        {
            Node() = default;
            Node(const T& t, Node* left, Node* right, const typename std::vector<Element>::iterator& parent)
            {
                _parent = parent;
                _elems.emplace_back(t, this, left, right);
            }

            void destroy()
            {
                _elems.clear();
            }
            virtual ~Node()
            {
                destroy();
            }
            std::vector<Element> _elems;
            typename std::vector<Element>::iterator             _parent;

            // in the elems array, find the first one large or equal one,
            // if can not find, return end()
            std::pair<typename std::vector<Element>::iterator, bool>
                find_equal_or_large(const T& val)
            {
                typename std::vector<Element>::iterator it = _elems.begin();
                for (;it != _elems.end(); ++ it)
                {
                    if (it->_val >= val)
                    {
                        return std::make_pair(it, true);
                        // return std::make_pair<typename std::vector<Element>::iterator, bool>(it, true);
                    }
                }
                return std::make_pair<typename std::vector<Element>::iterator, bool>(_elems.end(), false);
            }
        };

        Node*     _root{nullptr};
        size_type _elem_count{0};
        size_t    _max_elem_in_node;

        Node* _dummy; //FIXME
        // Node      _dummy_begin;
        // Node      _dummy_end;

        typename std::vector<Element>::iterator _dummy_begin_iter() const
        {
            assert(_dummy->_elems.size() != 0U);
            // if (_dummy_begin._elems() == 0)
            // {
            //     _dummy_begin._elems.emplace_back(HEAD_ELEMENT, &_begin_elem);
            // }
            return _dummy->_elems.begin();
        }

        typename std::vector<Element>::iterator _dummy_end_iter() const
        {

            assert(_dummy->_elems.size() != 0U);
            return _dummy->_elems.end();
        }

        // typename std::vector<Element>::const_iterator last_iter(typename std::vector<Element>& v) const
        // {
        //     if (v.begin() == v.end())
        //     {
        //         return v.end();
        //     }
        //     return v.end() - 1;
        //
        // }

        typename std::vector<Element>::iterator last_iter(typename std::vector<Element>& v) const
        {
            if (v.begin() == v.end())
            {
                return v.end();
            }
            return v.end() - 1;

        }


        typename std::vector<Element>::iterator _first_elem_iter() const
        {
            return _dummy_begin_iter()->_right->_elems.begin();
        }

        typename std::vector<Element>::iterator _last_elem_iter() const
        {
            return last_iter(_dummy_end_iter()->_left->_elems);
        }

        // XXX caller should make sure it is not the end() of vector
        // REMOVE
        Element* _iter_to_elem(const typename std::vector<Element>::iterator& it) const
        {
            assert(it != it->_owner->_elems.end());
            return &(*it);
        }

        bool _has_left_children_node(const Element* el) const
        {
            if (el->_left == nullptr)
            {
                return false;
            }
            if (el->_left == _dummy)
            {
                return false;
            }
            return true;
        }

        bool _has_right_children_node(const Element* el) const
        {
            if (el->_right == nullptr)
            {
                return false;
            }
            if (el->_right == _dummy)
            {
                return false;
            }
            return true;
        }

        typename std::vector<Element>::iterator find_elem(const T& elem) const
        {
            if (_root == nullptr)
            {
                return _dummy_end_iter();
            }
            Node* cur = _root;
            while (true)
            {
                auto it_bool_pair = cur->find_equal_or_large(elem);
                // have find the one exactly equal to elem
                if (it_bool_pair.second == true && it_bool_pair.first->_val == elem)
                {
                    return it_bool_pair.first;
                }
                // the elems array not full, so there is no possible for them have children nodes. stop here.
                if (cur->_elems.size() < _max_elem_in_node)
                {
                    return _dummy_end_iter();
                }
                else //if (it_bool_pair.second != )
                {
                    // find one elem bigger than val, then should look at its _left branch
                    if (it_bool_pair.second == true)
                    {
                        if (_has_left_children_node(_iter_to_elem(it_bool_pair.first)))
                        {
                            cur = it_bool_pair.first->_left;
                            continue;
                        }
                        return _dummy_end_iter();
                    }
                    else
                    {
                        const Element* last = _iter_to_elem(last_iter(cur->_elems));
                        if (_has_right_children_node(last))
                        {
                            cur = last->_right;
                            continue;
                        }
                        return _dummy_end_iter();
                    }
                }
            }
            assert(0);
            return _dummy_end_iter();
        }



        void update_begin_end(Element* el)
        {
            assert(el != NULL);

            Element* first_elem = _iter_to_elem(_first_elem_iter());
            Element* last_elem = _iter_to_elem(_last_elem_iter());

            // smaller than current smallest one, update _dummy_begin
            assert(el->_owner != nullptr);
            if (el->_val < first_elem->_val)
            {
                assert(el->_left == nullptr);
                assert(first_elem->_left == _dummy);
                assert(_dummy_begin_iter()->_right == first_elem->_owner);

                el->_left = _dummy;
                first_elem->_left = nullptr;
                _dummy_begin_iter()->_right = el->_owner;
            }
            if (el->_val > last_elem->_val)
            {
                assert(el->_right == nullptr);
                assert(last_elem->_right == _dummy);
                assert(_dummy_end_iter()->_left == last_elem->_owner);
                el->_right = _dummy;
                last_elem->_right = nullptr;
                _dummy_end_iter()->_left = el->_owner;
            }
        }

        // should only called at the very begin
        void init_node_iter(Node* begin = nullptr, Node* end = nullptr)
        {
            _dummy_begin_iter()->_left = nullptr;
            _dummy_end_iter()->_right = nullptr;
            _dummy_begin_iter()->_right = begin;
            _dummy_end_iter()->_left = end;
            if (begin != nullptr)
            {
                assert(end == begin);
                begin->_elems.begin()->_left = _dummy;
                begin->_elems.begin()->_right = _dummy;
                // begin->_left = &_dummy_begin;
                // end->_right = &_dummy_end;
            }
        }

        void clear()
        {
            if (_root != nullptr)
            {
                _root->destroy();
                delete _root;
                _root = nullptr;
            }
            if (_dummy != nullptr)
            {
                delete _dummy;
                _dummy = nullptr;
            }
            init_node_iter();
            _elem_count = 0;
        }

        bool empty() const
        {
            if (_root == nullptr)
            {
                assert(0 == _elem_count);
                return true;
            }
            // assert(_dummy_begin._right != nullptr);
            // assert(_dummy_end._right != nullptr);

            assert(_root->_elems.size() != 0U);
            return false;
        }

        void shallow_free()
        {
            _root = nullptr;
            _elem_count = 0;
            clear();
        }

        void shallow_copy(btree<T>& rhs)
        {
            assert(empty());
            _elem_count = rhs._elem_count;
            _max_elem_in_node = rhs._max_elem_in_node;
            _root = rhs._root;
            init_node_iter(rhs._dummy_begin_iter()->_right, rhs._dummy_end_iter()->_left);
        }

        void deep_copy(const btree<T>& rhs)
        {
            assert(_root == nullptr);
            _elem_count = rhs._elem_count;
            _max_elem_in_node = rhs._max_elem_in_node;

            _root = new Node();
            init_node_iter(_root, _root);


            struct NodeInfo
            {
                Node* from_node;
                typename std::vector<Element>::iterator to_parent;
                Node* to_node;
                NodeInfo(Node* from, Node* to, const typename std::vector<Element>::iterator& it)
                {
                    from_node = from;
                    to_node = to;
                    to_parent = it;
                }
            };
            std::queue<NodeInfo> q;
            q.push(NodeInfo(rhs._root, _root, _dummy_end_iter()));
            while (!q.empty())
            {
                NodeInfo ni = q.front();
                q.pop();
                for (auto i : ni.from_node->_elems)
                {
                    ni.to_node->_elems.emplace_back(i._val, ni.to_node, nullptr, nullptr);
                }
                typename std::vector<Element>::iterator it = ni.to_node->_elems.begin();
                for (auto i : ni.from_node->_elems)
                {
                    update_begin_end(_iter_to_elem(it));
                    if (_has_left_children_node(&i))
                    {
                        Node* tmp = new Node();
                        tmp->_parent = ni.to_parent;
                        it->_left = tmp;
                        q.push(NodeInfo(i._left, tmp, it));
                    }
                    if (_has_right_children_node(&i))
                    {
                        assert(it + 1 == ni.to_node->_elems.end());
                        Node* tmp = new Node();
                        tmp->_parent = ni.to_parent;
                        it->_right = tmp;
                        q.push(NodeInfo(i._right, tmp, it));
                    }
                    assert(it != ni.to_node->_elems.end());
                    it ++;
                }
            }
        }

        // TODO make it non-recursive
        typename std::vector<Element>::iterator right_most_iter(const typename std::vector<Element>::iterator& cur_iter) const
        {
            if (!_has_right_children_node(_iter_to_elem(cur_iter)))
            {
                return cur_iter;
            }
            return right_most_iter(last_iter(cur_iter->_right->_elems));
        }



        typename std::vector<Element>::iterator left_most_iter(const typename std::vector<Element>::iterator& cur_iter) const
        {
            if (!_has_left_children_node(_iter_to_elem(cur_iter)))
            {
                return cur_iter;
            }
            else
            {
                return left_most_iter(cur_iter->_left->_elems.begin());
            }
        }



        typename std::vector<Element>::iterator backward_iter(const typename std::vector<Element>::iterator& cur_iter) const
        {
            typename std::vector<Element>::iterator ret = _dummy_end_iter();
            if (cur_iter == ret)
            {
                if (_root != nullptr)
                {
                    ret = _last_elem_iter();
                }
            }
            else
            {
                Node* cur_node = cur_iter->_owner;
                assert(cur_iter != cur_node->_elems.end()); // never locate at end()
                // if ()
                if (_has_left_children_node(_iter_to_elem(cur_iter)))
                {
                    ret = right_most_iter(last_iter(cur_iter->_left->_elems));
                }

                if (cur_iter == cur_node->_elems.begin()) // can move to right elem
                {
                    if (cur_iter != _first_elem_iter())
                    {
                        ret = cur_node->_parent;
                    }
                }
                else
                {
                    ret = cur_iter - 1;
                }
            }
            return ret;
        }


        typename std::vector<Element>::iterator  forward_iter(const typename std::vector<Element>::iterator& cur_iter) const
        {
            typename std::vector<Element>::iterator ret = _dummy_end_iter();
            // forward to the begin
            if (cur_iter == ret)
            {
                if (_root != nullptr)
                {
                    ret = _first_elem_iter();
                }
            }
            else
            {
                Node* cur_node = cur_iter->_owner;
                assert(cur_iter != cur_node->_elems.end()); // never locate at end()
                if (cur_iter + 1 != cur_node->_elems.end()) // can move to right elem
                {
                    // not the right most elem, should not have right child node
                    assert(!_has_right_children_node(_iter_to_elem(cur_iter + 1)));
                    // but need to check the smallest one first.
                    ret = left_most_iter(cur_iter + 1);
                }
                else
                {
                    // the last elem in array, must move to right node child
                    if (_has_right_children_node(_iter_to_elem(cur_iter)))
                    {
                        ret = left_most_iter(cur_iter->_right->_elems.begin());
                    }
                    else
                    {
                        // got back to parent
                        if (cur_iter != _last_elem_iter())
                            ret = cur_node->_parent;
                    }
                }
            }
            return ret;
        }
};


template<typename T>
btree<T>::btree(size_t maxNodeElems): _max_elem_in_node{maxNodeElems}
{

    _dummy = new Node();
    _dummy->_elems.emplace_back(DUMMY_EMELEMT, _dummy);
    // _dummy._elems.emplace_back(TAIL_ELEMENT, &_dummy_end);
    init_node_iter();
}

template<typename T>
btree<T>::~btree()
{
    // TODO
    clear();
}

template<typename T>
btree<T>::btree(const btree<T>& original)
{
    deep_copy(original);
}

template<typename T>
btree<T>::btree(btree<T>&& original) noexcept
{
    shallow_copy(original);
    original.shallow_free();
}

template<typename T>
btree<T>& btree<T>::operator=(const btree<T>& rhs)
{
    if (this != &rhs)
    {
        clear();
        deep_copy(rhs);
    }
    return *this;
}

template<typename T>
btree<T>& btree<T>::operator=(btree<T>&& rhs) noexcept
{
    if (this != &rhs)
    {
        clear();
        shallow_copy(rhs);
        rhs.shallow_free();
    }
    return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const btree<T>& tree)
{
    bool first = true;
    std::queue<typename btree<T>::Node*> q;
    q.push(tree._root);
    while (!q.empty())
    {
        typename btree<T>::Node* cur = q.front();
        q.pop();
        for (const auto& i : cur->_elems)
        {
            if (tree._has_left_children_node(&i))
            {
                q.push(i._left);
            }
            if (tree._has_right_children_node(&i))
            {
                q.push(i._right);
            }
            if (first)
            {
                first = false;
                os << i._val;
            }
            else
            {
                os << " " << i._val;
            }
        }
    }
    return os;
}

template<typename T>
typename btree<T>::iterator btree<T>::begin()
{
    if (empty())
    {
        return end();
    }
    return typename btree<T>::iterator{this, _first_elem_iter()};
}

template<typename T>
typename btree<T>::iterator btree<T>::end()
{
    return typename btree<T>::iterator(this, _dummy_end_iter());
}

template<typename T>
typename btree<T>::const_iterator btree<T>::cbegin() const
{
    if (empty())
    {
        return cend();
    }
    return typename btree<T>::const_iterator{this, _first_elem_iter()};
}

template<typename T>
typename btree<T>::const_iterator btree<T>::cend() const
{
    return typename btree<T>::const_iterator(this, _dummy_end_iter());
}

template<typename T>
typename btree<T>::iterator btree<T>::find(const T& elem)
{
    typename std::vector<Element>::iterator e = find_elem(elem);
    return typename btree<T>::iterator(this, e);
}

template<typename T>
typename btree<T>::const_iterator btree<T>::find(const T& elem) const
{
    auto e = find_elem(elem);
    return typename btree<T>::const_iterator(this, e);
}

template<typename T>
std::pair<typename btree<T>::iterator, bool> btree<T>::insert(const T& elem)
{
    assert(_max_elem_in_node > 0);
    if (_root == nullptr)
    {
        _root = new Node(elem, _dummy, _dummy, _dummy_end_iter());
        init_node_iter(_root, _root);
        _elem_count = 1;
        // _root->_elems.emplace_back(elem, _root, &_dummy_begin, &_dummy_end);
        // return std::make_pair<iterator, bool>(iterator(&(*_root->_elems.begin())), true);
        return std::make_pair<typename btree<T>::iterator, bool>(typename btree<T>::iterator(this, _first_elem_iter()), true);
    }

    typename std::vector<Element>::iterator parent = _dummy_end_iter();
    Node* cur = _root;
    typename btree<T>::iterator ret(this, _dummy_end_iter());
    bool _not_find = true;
    while (true)
    {
        auto it_bool_pair = cur->find_equal_or_large(elem);
        // already in btree
        if (it_bool_pair.second == true && it_bool_pair.first->_val == elem)
        {
            _not_find = false;
            ret = typename btree<T>::iterator(this, it_bool_pair.first);
            break;
        }
        // it should not have any children nodes, and insert here
        if (cur->_elems.size() < _max_elem_in_node)
        {
            ++ _elem_count;
            typename std::vector<Element>::iterator it = cur->_elems.emplace(it_bool_pair.first, elem, cur, nullptr, nullptr);
            update_begin_end(_iter_to_elem(it));
            ret = typename btree<T>::iterator(this, it);
            break;
        }
        // reach the max limited elems size
        else
        {
            if (it_bool_pair.second == true)
            {
                // recursive find in _left node
                if (_has_left_children_node(_iter_to_elem(it_bool_pair.first)))
                {
                    cur = it_bool_pair.first->_left;
                    parent = it_bool_pair.first;
                    continue;
                }
                // should create new left node, and be the first elem in this node
                else
                {
                    Node* n = new Node(elem, nullptr, nullptr, parent);
                    update_begin_end(_iter_to_elem(n->_elems.begin()));
                    it_bool_pair.first->_left = n;
                    ret = typename btree<T>::iterator(this, n->_elems.begin());
                    break;
                }
            }
            // the biggest one.
            else
            {
                Element* last = _iter_to_elem(last_iter(cur->_elems));
                if (_has_right_children_node(last))
                {
                    parent = last_iter(cur->_elems);
                    cur = last->_right;
                    continue;
                }
                else
                {
                    Node* n = new Node(elem, nullptr, nullptr, parent);
                    update_begin_end(_iter_to_elem(n->_elems.begin()));
                    last->_right = n;
                    ret = typename btree<T>::iterator(this, n->_elems.begin());
                    break;
                }
            }
        }
    }
    return std::make_pair(ret, _not_find);
}
#endif
