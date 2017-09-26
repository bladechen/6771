/**
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
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t difference_type;
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

        reverse_iterator rbegin() {return reverse_iterator{end()}};
        reverse_iterator rend() {return reverse_iterator{begin()}};
        const_reverse_iterator crbegin() const {return const_reverse_iterator{cend()}};
        const_reverse_iterator crend() const {return const_reverse_iterator{cbegin()}};
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
        ~btree() = default;

    private:
        struct Node;
        struct Element;

        enum ELEMENT_MARKER_E
        {
            HEAD_ELEMENT = 1,
            TAIL_ELEMENT = 2,
            NORMAL_ELEMENT = 3,
        };

        struct Element
        {
            Element(enum ELEMENT_MARKER_E m, Node* owner): _marker{m}, _owner{owner}{};
            Element(const T& t,
                    Node* owner, Node* left, Node* right, enum ELEMENT_MARKER_E m = NORMAL_ELEMENT)
                : _val{t}, _marker{m}, _right{left},_right{right}, _owner{owner}{};
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
            Node* _right{nullptr};
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
            Node(const T& t)
            {
                _elems.emplace_back(t, this, nullptr, nullptr);
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

            std::pair<std::vector<Element>::iterator, bool>
                find_equal_or_large(const T& val)
            {
                std::vector<Element>::iterator it = _elems.begin();
                for (it != _elems.end(); ++ it)
                {
                    if (it->_val >= val)
                    {
                        return std::make_pair<std::vector<Element>::iterator, bool>(it, true);
                    }
                }
                return std::make_pair<std::vector<Element>::iterator, bool>(_elems.end(), false);
            }
        };

        Node*     _root{nullptr};
        size_type _elem_count{0};
        size_t    _max_elem_in_node;

        Node      _dummy_begin;
        Node      _dummy_end;

        Element*  _dummy_begin_elem()
        {
            if (_dummy_begin._elems() == 0)
            {
                _dummy_begin._elems.emplace_back(HEAD_ELEMENT, &_begin_elem);
            }
            return &_dummy_begin._elems[0];
        }

        Element* _dummy_end_elem()
        {
            if (_dummy_end._elems() == 0)
            {
                _dummy_end._elems.emplace_back(TAIL_ELEMENT, &_end_elem);
            }
            return &_dummy_end._elems[0];
        }

        Element* _begin_elem()
        {
            return &_dummy_begin_elem()->_right->_elems[0];
        }

        Element* _end_elem()
        {
            return &_dummy_end_elem()->_right->_elems[_dummy_end_elem()->_right->_elems.size() - 1];
        }

        bool _has_left_children_node(const Element* el)
        {
            if (el->_left == nullptr)
            {
                return false;
            }
            if (el->_left == _dummy_begin_elem())
            {
                return false;
            }
            return true;
        }

        bool _has_right_children_node(const Element* el)
        {
            if (el->_right == nullptr)
            {
                return false;
            }
            if (el->_right == _dummy_end_elem())
            {
                return false;
            }
            return true;
        }

        Element* find_elem(const T& val) const
        {
            if (_root == nullptr)
            {
                return nullptr;
            }
            Node* cur = _root;
            while (true)
            {
                auto it_bool_pair = cur->find_equal_or_large(elem);
                if (it_bool_pair.second == true && it_bool_pair.first->_val == elem)
                {
                    return &(*it_bool_pair.first);
                }
                if (cur->_elems.size() < _max_elem_in_node)
                {
                    return nullptr;
                }
                else
                {
                    if (it_bool_pair.second == true)
                    {
                        if (_has_left_children_node(&(*it_bool_pair.first)))
                        {
                            cur = it_bool_pair.first->_left;
                            continue;
                        }
                        return nullptr;
                    }
                    else
                    {
                        Element* last = &cur->elems[cur->elems.size() - 1];
                        if (_has_right_children_node(last))
                        {
                            cur = last;
                            continue;
                        }
                        return nullptr;
                    }
                }
            }
            return std::make_pair(ret, true);
        }

        void update_begin_end(Element* el)
        {
            assert(el != NULL);

            Element* first_elem = _begin_elem();
            Element* last_elem = _end_elem();
            if (el->_val < first_elem->_val)
            {
                assert(el->_left== nullptr);
                assert(first_elem->_left == &_dummy_begin);
                assert(_dummy_begin_elem()->_right == first_elem->_owner);
                el->_left = &_dummy_begin;
                first_elem->_left = nullptr;
                _dummy_begin_elem()->_right = el;
            }
            if (el->_val > last_elem->_val)
            {
                assert(el->_right == nullptr);
                assert(last_elem->_right == &_dummy_end);
                assert(_dummy_end_elem()->_left == last_elem->_owner);
                el->_right = &_dummy_end;
                last_elem->_right = nullptr;
                _dummy_end_elem()->_left = el;
            }
        }

        void init(Node* begin = nullptr, Node* end = nullptr)
        {
            _dummy_begin_elem()->_left = nullptr;
            _dummy_end_elem()->_right = nullptr;
            _dummy_begin_elem()->_right = begin;
            _dummy_end_elem()->_left = end;
            if (begin != nullptr)
            {
                assert(end != nullptr);
                begin->_left = &_dummy_begin;
                end->_right = &_dummy_end;
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
            _elem_count = 0;
        }

        bool empty()
        {
            if (_root == nullptr)
            {
                assert(0 == _elem_count);
                return true;
            }
            // assert(_dummy_begin._right != nullptr);
            // assert(_dummy_end._right != nullptr);

            assert(_root->size() != 0U);
            return false;
        }

        void shallow_free()
        {
            _root = nullptr;
            _elem_count = 0;
            init(nullptr);
        }

        void shallow_copy(const btree<T>& rhs)
        {
            assert(empty());
            _elem_count = rhs._elem_count;
            _max_elem_in_node = rhs._max_elem_in_node;
            _root = rhs._root;
            init(rhs._dummy_begin_elem()->_right, rhs._dummy_end_elem()->_left);
        }

        void deep_copy(const btree<T>& rhs)
        {
            assert(!_root->size());
            _elem_count = rhs._elem_count;
            _max_elem_in_node = rhs._max_elem_in_node;

            // TODO

        }

};


template<typename T>
btree<T>::btree(size_t maxNodeElems): _max_elem_in_node{maxNodeElems}
{
    init();
}

template<typename T>
btree<T>::~btree()
{
    clear();
}

template<typename T>
btree<T>::btree(const btree<T>& original)
{
    deep_copy(original);
}

template<typename T>
btree<T>::btree(btree<T>&& original)
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
btree<T>& btree<T>::operator=(btree<T>&& rhs)
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
    std::queue<Node*> q;
    q.push(_root);
    while (!q.empty())
    {
        Node* cur = q.front();
        q.pop();
        for (const auto& i : cur->elems)
        {
            if (_has_left_children_node(&i))
            {
                q.push(i._left);
            }
            if (_has_right_children_node(&i))
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
}

template<typename T>
iterator btree<T>::begin()
{
    if (empty())
    {
        return end();
    }
    return iterator{_begin_elem()};
}

template<typename T>
iterator btree<T>::end()
{
    return iterator(_dummy_end_elem());
}

template<typename T>
const_iterator btree<T>::cbegin() const
{
    if (empty())
    {
        return cend();
    }
    return const_iterator{_begin_elem()};
}

template<typename T>
const_iterator btree<T>::cend() const
{
    return const_iterator(_dummy_end_elem());
}

template<typename T>
iterator btree<T>::find(const T& elem)
{
    auto e = find_elem(elem);
    if (e == nullptr)
    {
        return end();
    }
    return iterator(e);
}

template<typename T>
const_iterator btree<T>::find(const T& elem) const
{
    auto e = find_elem(elem);
    if (e == nullptr)
    {
        return end();
    }
    return const_iterator(e);
}


template<typename T>
std::pair<iterator, bool> btree<T>::insert(const T& elem)
{
    assert(_max_elem_in_node > 0); //TODO check spec
    if (_root == nullptr)
    {
        _root = new Node();
        init(&_root, &_root);
        _elem_count = 1;
        _root->_elems.emplace_back(elem, _root, &_dummy_begin, &_dummy_end);
        return std::make_pair<iterator, bool>(iterator(&(*_root->_elems.begin())), true);
    }

    Node* cur = _root;
    iterator ret;
    while (true)
    {
        // can insert to this node.
        auto it_bool_pair = cur->find_equal_or_large(elem);
        if (it_bool_pair.second == true && it_bool_pair.first->_val == elem)
        {
            return std::make_pair(iterator(&(*it_bool_pair.first)), false);
        }
        // it should not have any children node, and insert here
        if (cur->_elems.size() < _max_elem_in_node)
        {
            ++ _elem_count;
            std::vector<Element>::it = cur->_elems.emplace(it_bool_pair.first, cur, nullptr, nullptr);
            update_begin_end(&(*it));
            ret = iterator(&(*it));
        }
        // reach the max limited node size
        else
        {
            // insert _left part
            if (it_bool_pair.second == true)
            {
                // recursive find
                if (_has_left_children_node(&(*it_bool_pair.first)))
                {
                    cur = it_bool_pair.first->_left;
                    continue;
                }
                else
                {
                    Node* n = new Node(elem);
                    update_begin_end(&(n->elems[0]));
                    it_bool_pair.first->_left = n;
                    ret = iterator(&(n->elems[0]));
                    break;
                }
            }
            // the biggest one.
            else
            {
                Element* last = &cur->elems[cur->elems.size() - 1];
                if (_has_right_children_node(last))
                {
                    cur = last;
                    continue;
                }
                else
                {
                    Node* n = new Node(elem);
                    update_begin_end(&(n->elems[0]));
                    last->_left = n;
                    ret = iterator(&(n->elems[0]));
                    break;
                }
            }
        }
    }
    return std::make_pair(ret, true);
}
#endif
