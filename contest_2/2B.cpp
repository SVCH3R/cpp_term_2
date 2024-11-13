#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, m, input;
  std::cin >> n;
  std::vector<int> v;
  for (int i = 0; i < n; ++i) {
    std::cin >> input;
    v.emplace_back(input);
  }
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    std::cin >> input;
    std::cout << std::upper_bound(v.begin(), v.end(), input) -
                     std::lower_bound(v.begin(), v.end(), input)
              << '\n';
  }
}
