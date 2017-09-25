#pragma once
#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

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

                bool addNode(const N& val);
                bool addEdge(const N& src, const N& dst, const E& w);
                bool replace(const N& oldData, const N& newData);

                void mergeReplace(const N& oldData, const N& newData);
                void deleteNode(const N&) noexcept;
                void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
                void clear() noexcept;

                bool isNode(const N& val) const;
                bool isConnected(const N& src, const N& dst) const;

                // make std::ostream& for fuzzier test.
                void printNodes(std::ostream& os = std::cout) const;
                void printEdges(const N& val, std::ostream& os = std::cout) const;

                // simulate iterator
                void begin() const;
                bool end() const;
                void next() const;
                const N& value() const;

            private:
                class Node;
                class Edge;

                std::map<N, std::shared_ptr<Node>> _nodes_map; // store all the Node in this graph
                mutable typename std::map<N, std::shared_ptr<Node>>::const_iterator _it;

                static bool _is_same_id(const N& l, const N& r);
                static bool _is_same_weight(const E& l, const E& r);

                void _deep_copy(const Graph& g);
                void _insert_edge(std::shared_ptr<Node> src_node,
                                  std::shared_ptr<Node> dst_node,
                                  const E& weight);

                class Edge
                {
                    public:
                        Edge(const std::shared_ptr<Node>& dst, const E& weight);
                        std::weak_ptr<Node> _dst;  // refer to the node in the _nodes_map
                        E _weight;
                };

                class EdgeLessOperator
                {
                    public:
                        bool operator () (const std::unique_ptr<Edge>& a, const std::unique_ptr<Edge>& b)
                        {
                            const auto& a_dst_node = a->_dst.lock();
                            const auto& b_dst_node = b->_dst.lock();
                            assert(a_dst_node != nullptr);
                            assert(b_dst_node != nullptr);
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
                        Node(const N& id);
                        bool is_out_edge(const N& dst, const E& weight);
                        void delete_edge(const N& dst, const E& weight) noexcept;

                        N _id;
                        std::set<std::unique_ptr<Edge>, EdgeLessOperator> _out; // the out going edge

                };
        };
        #include "Graph.tem"
}
