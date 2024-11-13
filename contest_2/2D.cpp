#include <algorithm>
#include <iostream>
#include <vector>

void Print(const std::vector<int>& v) {
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] + 1 << ' ';
  }
  std::cout << '\n';
}

class Graph {
 private:
  std::vector<std::vector<int>> edges_;

 public:
  explicit Graph(const int& n) : edges_(std::vector<std::vector<int>>(n)) {
  }
  void AddEdge(const int& v, const int& u) {
    edges_[v - 1].emplace_back(u - 1);

    edges_[u - 1].emplace_back(v - 1);
  }

  void Vertex(const int& u) {
    Print(edges_[u - 1]);
  }
  ~Graph() = default;
};

int main() {
  int n, k, input1, input2;
  std::cin >> n >> k;
  auto graph = Graph(n);
  for (int i = 0; i < k; ++i) {
    std::cin >> input1;
    if (input1 == 1) {
      std::cin >> input1 >> input2;
      graph.AddEdge(input1, input2);
    } else {
      std::cin >> input2;
      graph.Vertex(input2);
    }
  }
}
