#include <iostream>
#include <list>
#include <memory>
#include <set>

template <typename Node, typename Edge>
class Graph {
public:
  void emplace(const Node& n) {
    nodes.insert(std::make_shared<NodeWrapper>(n));
  }

  void print() const {
    for (const auto& node : nodes)
      std::cout << node->n << '\n';
    // TODO: update print so it prints edges as well
  }

  void deleteNode(const Node& todelete) noexcept {
    // TODO: this
  }

  void addEdge(const Node& from, const Node& to, const Edge& e)  {
    // TODO: this
  }

private:
  struct NodeWrapper;

  struct EdgeWrapper {
    EdgeWrapper(const Edge& e, const std::shared_ptr<NodeWrapper>& n): e{e}, n{n} {}
    // TODO: e occurs twice. Once in the incoming edge, once in the outgoing edge. How can we make this more memory efficient? Is this a good idea?
    Edge e;
    std::weak_ptr<NodeWrapper> n;
  };

  struct NodeWrapper {
    NodeWrapper(const Node& n): n{n} {}

    Node n;
    mutable std::list<EdgeWrapper> outgoing;
    mutable std::list<EdgeWrapper> incoming;
  };
  std::set<std::shared_ptr<NodeWrapper>> nodes;
};

int main() {
  Graph<std::string, std::string> g;
  g.emplace("hello");
  g.emplace("world");
  g.emplace("a");
  g.emplace("b");
  g.emplace("c");

  // TODO: why doesn't this print in the correct order? How can we fix this?
  g.print();
}
