#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  int n, x;
  std::cin >> n;
  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }
  std::cin >> x;
  std::cout << count(v.begin(), v.end(), x);
}