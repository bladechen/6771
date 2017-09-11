#pragma once

#include <map>
#include <algorithm>
#include <cassert>
#include <vector>
#include <set>
#include <memory>
#include <utility>
#include <exception>
#include <iostream>
#include <string>
namespace gdwg
{
    template <typename N, typename E>
    class Graph
    {
        public:
            Graph();
            Graph(const Graph& g);
            Graph(Graph&& g);

            Graph& operator=(const Graph& g);
            Graph& operator=(Graph&& g);
            // virtual ~Graph(); XXX

            bool addNode(const N& val);
            bool addEdge(const N& src, const N& dst, const E& w);
            bool replace(const N& oldData, const N& newData);

            void mergeReplace(const N& oldData, const N& newData);
            void deleteNode(const N&) noexcept;
            void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
            void clear() noexcept;
            bool isNode(const N& val) const;
            bool isConnected(const N& src, const N& dst) const;
            void printNodes(std::ostream& os = std::cout) const;
            void printEdges(const N& val, std::ostream& os=std::cout) const;

            void begin() const;
            bool end() const;
            void next() const;
            const N& value() const;

        // public:
        private:

            static bool _is_same_id(const N& l, const N& r);

            static bool _is_same_weight(const E& l, const E& r);
            void _deep_copy(const Graph& g);

            class Node;
            class Edge;


            void _insert_edge(std::shared_ptr<Node> src_node,
                              std::shared_ptr<Node> dst_node,
                              const E& weight);

            std::map<N, std::shared_ptr<Node> > _nodes_map;
            mutable typename std::map<N, std::shared_ptr<Node> >::const_iterator _it;


            class Edge
            {
                public:
                    Edge(const std::shared_ptr<Node>& src, const std::shared_ptr<Node>& dst, const E& weight)
                        :_src(src), _dst(dst), _weight(weight)
                    {

                    }
                    std::weak_ptr<Node> _src;
                    std::weak_ptr<Node> _dst;
                    E _weight;
            };

            class EdgeLessOperator
            {
                public:
                    bool operator () (const std::unique_ptr<Edge>& a, const std::unique_ptr<Edge>& b)
                    {
                        const auto& a_src_node = a->_src.lock();
                        const auto& a_dst_node = a->_dst.lock();
                        const auto& b_src_node = b->_src.lock();
                        const auto& b_dst_node = b->_dst.lock();
                        assert(a_src_node != nullptr);
                        assert(a_dst_node!= nullptr);
                        assert(b_src_node != nullptr);
                        assert(b_dst_node != nullptr);
                        if (!_is_same_id(a_src_node->_id , b_src_node->_id))
                        {
                            return a_src_node->_id < b_src_node->_id;
                        }
                        if (!_is_same_id(a_dst_node->_id , b_dst_node->_id))
                        {
                            return a_dst_node->_id < b_dst_node->_id;
                        }
                        return a->_weight < b->_weight;
                    }
            };

            class Node
            {
                public:
                    Node(const N& id);//:_id{id} {};
                    N _id;
                    // std::set<std::shared_ptr<Edge>, EdgeLessOperator> _in;
                    std::set<std::unique_ptr<Edge>, EdgeLessOperator> _out;


                    // bool is_in_edge(const N& src, const E& weight)
                    // {
                    //     if (_in.find(std::make_shared<Edge>(std::make_shared<Node>(src),
                    //                                         std::make_shared<Node>(_id),
                    //                                         weight))
                    //         != _in.end())
                    //     {
                    //         return true;
                    //     }
                    //     return false;
                    //
                    // }
                    bool is_out_edge(const N& dst, const E& weight) noexcept
                    {
                        for (auto i = _out.cbegin(); i != _out.cend(); ++ i)
                        {
                            auto src_node = (*i)->_src.lock();
                            auto dst_node = (*i)->_dst.lock();
                            assert(src_node && dst_node);
                            assert(_is_same_id(src_node->_id , _id));
                            if (_is_same_id(dst_node->_id, dst) && _is_same_weight(weight, (*i)->_weight) )
                            {
                                return true;
                            }

                        }
                        return false;
                    }


                    void delete_edge(const N& dst, const E& weight) noexcept
                    {
                        if (!is_out_edge(dst, weight))
                        {
                            return;
                        }
                        for (auto i = _out.begin(); i != _out.end(); ++ i)
                        {
                            auto src_node = (*i)->_src.lock();
                            auto  dst_node = (*i)->_dst.lock();

                            assert(_is_same_id(src_node->_id , _id));
                            if (_is_same_id(dst_node->_id, dst) && _is_same_weight(weight, (*i)->_weight) )
                            {
                                _out.erase(i);
                                return;
                            }
                        }
                    }
                        // if (!is_out_edge(dst, weight))
                        // {
                        //     return;
                        // }
                        //
                        // _out.erase(std::make_shared<Edge>(std::make_shared<Node>(_id),

            };

            // Node
            friend bool operator< (const Node& a, const Node& b)
            {
                return a._id < b._id;
            }


            // Edge
            // friend


    };

    template<typename N, typename E>
    Graph<N, E>::Node::Node(const N& id):_id{id}{}



    template<typename N, typename E>
    Graph<N, E>::Graph()
    {

    }


    template<typename N, typename E>
    Graph<N, E>::Graph(const Graph<N, E>& g)
    {
        _deep_copy(g);
    }

    template<typename N, typename E>
    bool Graph<N, E>::_is_same_id(const N& l, const N& r)
    {
        return ((!(l < r)) && (!(r < l)));

    }

    template<typename N, typename E>
    bool Graph<N, E>::_is_same_weight(const E& l, const E& r)
    {
         return ((!(l < r)) && (!(r < l)));
    }



    template<typename N, typename E>
    void Graph<N, E>::_deep_copy(const Graph<N, E>& g)
    {
        for (auto i = g._nodes_map.begin(); i != g._nodes_map.end(); ++ i)
        {
            _nodes_map.insert(std::make_pair(i->first, std::make_shared<Graph<N, E>::Node>(i->first)));
        }
        for (auto i = g._nodes_map.begin(); i != g._nodes_map.end(); ++ i)
        {
            for (auto j = (i->second)->_out.begin(); j != (i->second)->_out.end(); ++ j)
            {
                assert((*j)->_dst.lock());
                assert(_nodes_map.find((*j)->_dst.lock()->_id) != _nodes_map.end());
                _insert_edge(_nodes_map[i->first], _nodes_map[(*j)->_dst.lock()->_id], (*j)->_weight);
            }
        }

    }

    template<typename N, typename E>
    Graph<N, E>::Graph(Graph<N, E>&& g)
    {
        // _nodes_map = g._nodes_map;
        _nodes_map = std::move(g._nodes_map);
        g._nodes_map.clear();
    }

    template<typename N, typename E>
    Graph<N, E>& Graph<N, E>::operator=(const Graph<N, E>& g)
    {
        if (this == &g)
        {
            return *this;
        }
        _nodes_map.clear();
        _deep_copy(g);
        return *this;
    }

    template<typename N, typename E>
    Graph<N, E> & Graph<N, E>::operator=(Graph<N, E>&& g)
    {
        if (this == &g)
        {
            return *this;
        }
        _nodes_map.clear();
        _nodes_map = std::move(g._nodes_map);
        // _nodes_map = g._nodes_map;
        g._nodes_map.clear();
        return *this;
    }

    template<typename N, typename E>
    bool Graph<N, E>::addNode(const N& val)
    {
        if (_nodes_map.find(val) != _nodes_map.end())
        {
            return false;
        }
        assert(_nodes_map.insert(std::make_pair(val, std::make_shared<Graph<N, E>::Node>(val))).second);
        // _nodes_map.insert(std::make_pair(val, std::make_shared<Graph<N, E>::Node>(val)));
        return true;
    }

    template<typename N, typename E>
    void Graph<N, E>::_insert_edge(std::shared_ptr<Node> src_node,
                                   std::shared_ptr<Node> dst_node,
                                   const E& weight)
    {
        src_node->_out.insert(std::make_unique<Edge>(src_node, dst_node, weight));
        // dst_node->_in.insert(std::make_shared<Edge>(src_node, dst_node, weight));

    }

    template<typename N, typename E>
    bool Graph<N, E>::addEdge(const N& src, const N& dst, const E& w)
    {
        if (_nodes_map.find(src) == _nodes_map.end() || _nodes_map.find(dst) == _nodes_map.end())
        {
            throw std::runtime_error("either src or dst is not in the graph");
        }
        assert(_nodes_map.find(src) != _nodes_map.end());
        assert(_nodes_map.find(dst) != _nodes_map.end());
        auto src_node = _nodes_map[src]; //FIXME
        auto dst_node = _nodes_map[dst];
        assert(_is_same_id(src_node->_id , src));
        assert(_is_same_id(dst_node->_id , dst));

        if (src_node->is_out_edge(dst, w))
        {
            // assert(dst_node->is_in_edge(src, w));
            return false;
        }
        // assert(!dst_node->is_in_edge(src, w));
        _insert_edge(src_node, dst_node, w);
        return true;
    }

    template<typename N, typename E>
    bool Graph<N, E>::replace(const N& oldData, const N& newData)
    {
        if (_nodes_map.find(oldData) == _nodes_map.end())
        {
            throw std::runtime_error("not find old Data in replace");
        }
        if (_nodes_map.find(newData) != _nodes_map.end())
        {
            return false;
        }
        if (_is_same_id(oldData, newData))
        {
            return true;
        }
        assert(_nodes_map.find(newData) == _nodes_map.end());
        _nodes_map[newData] = _nodes_map[oldData];
        _nodes_map[newData]->_id = newData;
        _nodes_map.erase(oldData);
        // assert(_nodes_map.insert(std::make_pair(val, std::move(_nodes_map[oldData]))).second);

        // _nodes_map.insert(std::make_pair(newData, std::move(_nodes_map[oldData])));
        // _nodes_map[newData]->_id = newData;
        // _nodes_map.erase(oldData);
        return true;
    }

    template<typename N, typename E>
    void Graph<N, E>::mergeReplace(const N& oldData, const N& newData)
    {
        if (_nodes_map.find(oldData) == _nodes_map.end() || _nodes_map.find(newData) == _nodes_map.end())
        {
            throw std::runtime_error("not find Data in mergeReplace");
        }

        if (_is_same_id(oldData, newData))
        {
            return;
        }
        auto src = _nodes_map[oldData];
        auto dst = _nodes_map[newData];

        for (auto i = _nodes_map.begin(); i != _nodes_map.end(); ++ i)
        {
            // from node not the deleted node
            if (!_is_same_id(i->second->_id ,oldData))
            {
                std::vector<E> tmp;
                for (auto j = (i->second)->_out.begin(); j != (i->second)->_out.end();)
                {
                    auto dst_node = (*j)->_dst.lock(); //out node
                    assert(dst_node);
                    if (_is_same_id(dst_node->_id,  oldData ))
                    {
                        tmp.push_back((*j)->_weight);
                        j = (i->second)->_out.erase(j);
                        // remove edge to the deleted node
                    }
                    else
                    {
                        ++ j;
                    }
                }
                for (auto j = tmp.begin(); j != tmp.end(); ++ j)
                {
                    if (!((i->second)->is_out_edge(newData, *j)))
                    {
                        _insert_edge(i->second, dst, *j);
                    }
                }
            }
        }

        for (auto i = src->_out.cbegin(); i != src->_out.cend(); ++ i)
        {
            auto node = (*i)->_dst.lock();
            assert(node);
            assert(_is_same_id((*i)->_src.lock()->_id , oldData));
            if (!_is_same_id(node->_id , oldData))
            {
                if (dst->is_out_edge(node->_id, (*i)->_weight))
                {
                    continue;
                }
                _insert_edge(dst, node,  (*i)->_weight);
                // dst->_out.insert(std::make_shared<Edge>(dst, node, (*i)->_weight));
            }
            else
            {
                if (!(dst->is_out_edge(dst->_id,  (*i)->_weight)))
                    _insert_edge(dst, dst,  (*i)->_weight);
                    // dst->_out.insert(std::make_shared<Edge>(dst, dst, (*i)->_weight));

            }
        }

        _nodes_map.erase(oldData);
    }

    template<typename N, typename E>
    void Graph<N, E>::deleteNode(const N& src) noexcept
    {
        if (_nodes_map.find(src) == _nodes_map.end() )
        {
            return;
        }
        for (auto i = _nodes_map.begin(); i != _nodes_map.end(); ++ i)
        {
            if (!_is_same_id(i->second->_id , src))
            {

                std::vector<E> tmp;
                for (auto j = (i->second)->_out.begin(); j != (i->second)->_out.end();)
                {
                    auto dst_node = (*j)->_dst.lock(); //out node
                    if (_is_same_id(dst_node->_id, src))
                    {
                        j = (i->second)->_out.erase(j);
                    }
                    else
                    {
                        ++ j;
                    }
                }
            }
        }
        _nodes_map.erase(src);
    }

    template<typename N, typename E>
    void Graph<N, E>::deleteEdge(const N& src, const N& dst, const E& w) noexcept
    {
        if (_nodes_map.find(src) == _nodes_map.end() || _nodes_map.find(dst) == _nodes_map.end())
        {
            return;
        }
        auto src_node = _nodes_map[src]; //FIXME
        auto dst_node = _nodes_map[dst];
        assert(_is_same_id(src_node->_id, src));
        assert(_is_same_id(dst_node->_id, dst));
        src_node->delete_edge(dst, w);

    }

    template<typename N, typename E>
    void Graph<N, E>::clear() noexcept
    {
        _nodes_map.clear();
    }

    template<typename N, typename E>
    bool Graph<N, E>::isNode(const N& val) const
    {
        return (_nodes_map.find(val) != _nodes_map.end());

    }

    template<typename N, typename E>
    bool Graph<N, E>::isConnected(const N& src, const N& dst) const
    {
        if (_nodes_map.find(src) == _nodes_map.end() || _nodes_map.find(dst) == _nodes_map.end())
        {
            throw std::runtime_error("either src or dst is not in the graph while calling isConnected");
        }
        auto src_node = _nodes_map.find(src)->second;
        auto dst_node = _nodes_map.find(dst)->second;
        assert(_is_same_id(src_node->_id , src));
        assert(_is_same_id(dst_node->_id , dst));

        return std::find_if(src_node->_out.cbegin(), src_node->_out.cend(), [&](const std::unique_ptr<Edge>& a) -> bool
                         {
                            return (_is_same_id(a->_src.lock()->_id , src) && _is_same_id(a->_dst.lock()->_id, dst));

                         }) !=  src_node->_out.cend();
    }

    template<typename N, typename E>
    void Graph<N, E>::printNodes(std::ostream& os) const
    {
        std::vector<std::shared_ptr<Node> > tmp;
        for (auto i = _nodes_map.begin(); i != _nodes_map.end(); ++ i)
        {
            tmp.push_back(i->second);
        }
        std::sort(tmp.begin(), tmp.end(),
                  [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) ->bool
                  {
                        if (a->_out.size() != b->_out.size())
                        {
                            return a->_out.size() < b->_out.size();
                        }
                        else
                        {
                            return a->_id < b ->_id;
                        }
                  }
                  );
        for (auto i = tmp.cbegin(); i != tmp.cend(); ++ i)
        {
            os << (*i)->_id << std::endl;
        }
    }
    template<typename N, typename E>
    void Graph<N, E>::printEdges(const N& val, std::ostream& os) const
    // void Graph<N, E>::printEdges(const N& val) const
    {
        if (_nodes_map.find(val) == _nodes_map.end())
        {
            throw std::runtime_error("no thing to printEdges");
        }
        os << "Edges attached to Node " << val << std::endl;// XXX overload ostream<<?
        auto node = _nodes_map.find(val)->second;
        if (node->_out.size() == 0)
        {
            os << "(null)" << std::endl;
            return;
        }

        std::vector<std::pair<N, E> > tmp;
        for (auto i = node->_out.cbegin(); i != node->_out.cend(); ++ i)
        {
            tmp.push_back(std::make_pair((*i)->_dst.lock()->_id,(*i)->_weight));
        }

        std::sort(tmp.begin(), tmp.end(),
                  [](const std::pair<N, E>& a, const std::pair<N, E>& b) ->bool
                  {
                        if (!_is_same_weight(a.second, b.second))
                        {
                            return a.second < b.second;
                        }
                        return a.first < b .first;
                  }
                  );
        for (auto i = tmp.cbegin(); i != tmp.cend(); ++ i)
        {
            os << i->first << " " << i->second << std::endl;
            // std::cout << i->first << " " << i->second << std::endl;
        }

    }

    template<typename N, typename E>
    void Graph<N, E>::begin() const
    {
        _it = _nodes_map.cbegin();

    }

    template<typename N, typename E>
    bool Graph<N, E>::end() const
    {
        return _it == _nodes_map.cend();

    }
    template<typename N, typename E>
    void Graph<N, E>::next() const
    {
        ++ _it;

    }

    template<typename N, typename E>
    const N& Graph<N, E>::value() const
    {
        return (_it->first);

    }


    // template<typename N, typename E>
    // void Graph<N, E>::fuck()
    // {
    //      Node a(10);
    //      Node b (100);
    //
    //     std::cout << (a < b) << std::endl;
    // }
    // template implementation
    // #include "Graph_tem.h"
}
