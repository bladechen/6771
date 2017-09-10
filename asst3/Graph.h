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
            void printNodes() const;
            void printEdges(const N& val) const;

            void begin() const;
            bool end() const;
            void next() const;
            const N& value() const;

            void fuck(); // FIXME delete me
        // public:
        private:

            void _deep_copy(const Graph& g);

            class Node;
            class Edge;


            void _insert_edge(std::shared_ptr<Node> src_node,
                              std::shared_ptr<Node> dst_node,
                              const E& weight);

            std::map<N, std::shared_ptr<Node> > _nodes_map;


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
                    bool operator () (const std::shared_ptr<Edge>& a, const std::shared_ptr<Edge>& b)
                    {
                        const auto& a_src_node = a->_src.lock();
                        const auto& a_dst_node = a->_dst.lock();
                        const auto& b_src_node = b->_src.lock();
                        const auto& b_dst_node = b->_dst.lock();
                        assert(a_src_node != nullptr);
                        assert(a_dst_node!= nullptr);
                        assert(b_src_node != nullptr);
                        assert(b_dst_node != nullptr);
                        if (a_src_node->_id != b_src_node->_id)
                        {
                            return a_src_node->_id < b_src_node->_id;
                        }
                        if (a_dst_node->_id != b_dst_node->_id)
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
                    std::set<std::shared_ptr<Edge>, EdgeLessOperator> _out;


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
                        if (_out.find(std::make_shared<Edge>(std::make_shared<Node>(_id),
                                                            std::make_shared<Node>(dst),
                                                            weight))
                            != _out.end())
                        {
                            return true;
                        }
                        return false;
                    }


                    void delete_edge(const N& dst, const E& weight) noexcept
                    {
                        if (!is_out_edge(dst, weight))
                        {
                            return;
                        }

                        _out.erase(std::make_shared<Edge>(std::make_shared<Node>(_id),
                                                          std::make_shared<Node>(dst),
                                                          weight));
                    }

                    void merge(const Node& src, const std::shared_ptr<Node>& myself)
                    {
                        assert(myself.get() == this);
                        for (auto i = src._out.cbegin(); i != src._out.cend(); ++ i)
                        {

                            auto node = (*i)->_dst.lock();
                            // pointing to myself, not merge
                            if (node->_id == _id)
                            {
                                continue;
                            }

                            if (is_out_edge(node->_id, (*i)->_weight))
                            {
                                continue;
                            }
                            _out.insert(std::make_shared<Edge>(myself, node, (*i)->_weight));
                        }
                    }
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
                _insert_edge(_nodes_map[i->first], _nodes_map[(*j)->_dst.lock()->_id], (*j)->_weight);
            }
        }

    }

    template<typename N, typename E>
    Graph<N, E>::Graph(Graph<N, E>&& g)
    {
        _nodes_map = g._nodes_map;
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
        _nodes_map = g._nodes_map;
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
        _nodes_map.insert(std::make_pair(val, std::make_shared<Graph<N, E>::Node>(val)));
        return true;
    }

    template<typename N, typename E>
    void Graph<N, E>::_insert_edge(std::shared_ptr<Node> src_node,
                                   std::shared_ptr<Node> dst_node,
                                   const E& weight)
    {
        src_node->_out.insert(std::make_shared<Edge>(src_node, dst_node, weight));
        // dst_node->_in.insert(std::make_shared<Edge>(src_node, dst_node, weight));

    }

    template<typename N, typename E>
    bool Graph<N, E>::addEdge(const N& src, const N& dst, const E& w)
    {
        if (_nodes_map.find(src) == _nodes_map.end() || _nodes_map.find(dst) == _nodes_map.end())
        {
            throw std::runtime_error("either src or dst is not in the graph");
        }
        auto src_node = _nodes_map[src]; //FIXME
        auto dst_node = _nodes_map[dst];
        assert(src_node->_id == src);
        assert(dst_node->_id == dst);
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
        _nodes_map.insert(std::make_pair(newData, std::move(_nodes_map[oldData])));
        _nodes_map[newData]->_id = newData;
        _nodes_map.erase(oldData);
        return true;
    }

    template<typename N, typename E>
    void Graph<N, E>::mergeReplace(const N& oldData, const N& newData)
    {
        if (_nodes_map.find(oldData) == _nodes_map.end() || _nodes_map.find(newData) == _nodes_map.end())
        {
            throw std::runtime_error("not find Data in mergeReplace");
        }

        if (oldData == newData)
        {
            return;
        }
        auto src = _nodes_map[oldData];
        auto dst = _nodes_map[newData];

        for (auto i = _nodes_map.begin(); i != _nodes_map.end(); ++ i)
        {
            if (i->second->_id != oldData)
            {

                std::vector<E> tmp;
                for (auto j = (i->second)->_out.begin(); j != (i->second)->_out.end();)
                {
                    auto dst_node = (*j)->_dst.lock(); //out node
                    if (dst_node->_id == oldData )
                    {
                        tmp.push_back((*j)->_weight);
                        j = (i->second)->_out.erase(j);
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

        // for (auto i = dst->_out.begin(); i != dst->_out.end(); )
        // {
        //     if ((*i)->_dst.lock()->_id == oldData)
        //     {
        //         i = dst->_out.erase(i);
        //     }
        //     else
        //     {
        //         ++ i;
        //     }
        // }
        //
        for (auto i = src->_out.cbegin(); i != src->_out.cend(); ++ i)
        {
            auto node = (*i)->_dst.lock();
            // pointing to myself, not merge
            if (dst->is_out_edge(node->_id, (*i)->_weight))
            {
                continue;
            }
            dst->_out.insert(std::make_shared<Edge>(dst, node, (*i)->_weight));
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
            if (i->second->_id != src)
            {

                std::vector<E> tmp;
                for (auto j = (i->second)->_out.begin(); j != (i->second)->_out.end();)
                {
                    auto dst_node = (*j)->_dst.lock(); //out node
                    if (dst_node->_id == src)
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
        assert(src_node->_id == src);
        assert(dst_node->_id == dst);
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
        assert(src_node->_id == src);
        assert(dst_node->_id == dst);
        return std::find_if(src_node->_out.cbegin(), src_node->_out.cend(), [&](const std::shared_ptr<Edge>& a) -> bool
                         {
                            return (a->_src.lock()->_id == src && a->_dst.lock()->_id == dst);

                         }) !=  src_node->_out.cend();
    }

    template<typename N, typename E>
    void Graph<N, E>::printNodes() const
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
            std::cout << (*i)->_id << std::endl;
        }
    }
    template<typename N, typename E>
    void Graph<N, E>::printEdges(const N& val) const
    {
        if (_nodes_map.find(val) == _nodes_map.end())
        {
            throw std::runtime_error("no thing to printEdges");
        }
        std::cout << "Edges attached to Node " << val << std::endl;// XXX overload ostream<<?
        auto node = _nodes_map.find(val)->second;
        if (node->_out.size() == 0)
        {
            std::cout << "(null)" << std::endl;
            return;
        }

        std::vector<std::pair<N, E> > tmp;
        for (auto i = node->_out.cbegin(); i != node->_out.cend(); ++ i)
        {
            auto edge = (*i);
            tmp.push_back(std::make_pair(edge->_dst.lock()->_id, edge->_weight));
        }

        std::sort(tmp.begin(), tmp.end(),
                  [](const std::pair<N, E>& a, const std::pair<N, E>& b) ->bool
                  {
                        if (a.second != b.second)
                        {
                            return a.second < b.second;
                        }
                        return a.first < b .first;
                  }
                  );
        for (auto i = tmp.cbegin(); i != tmp.cend(); ++ i)
        {
            std::cout << i->first << " " << i->second << std::endl;
        }

    }

    template<typename N, typename E>
    void Graph<N, E>::begin() const
    {

    }

    template<typename N, typename E>
    bool Graph<N, E>::end() const
    {

        return true;
    }
    template<typename N, typename E>
    void Graph<N, E>::next() const
    {

    }

    template<typename N, typename E>
    const N& Graph<N, E>::value() const
    {

    }


    template<typename N, typename E>
    void Graph<N, E>::fuck()
    {
         Node a(10);
         Node b (100);

        std::cout << (a < b) << std::endl;
    }
    // template implementation
    // #include "Graph_tem.h"
}
