#include <iostream>
#include <algorithm>
#include <vector>

template <class U, class T, class S>
struct Tripple {
  U first;
  T second;
  S third;
  Tripple(U f, T s, S t) : first(f), second(s), third(t){};
};

int main() {
  int n;
  std::cin >> n;
  std::vector<Tripple<int, int, int>> v;
  int tasks, fine;
  for (int i = 0; i < n; ++i) {
    std::cin >> tasks >> fine;
    v.emplace_back(Tripple<int, int, int>(tasks, fine, i + 1));
  }
  std::sort(v.begin(), v.end(), [](Tripple<int, int, int> v1, Tripple<int, int, int> v2) {
    if (v1.first != v2.first) {
      return v1.first > v2.first;
    }
    if (v1.second != v2.second) {
      return v1.second < v2.second;
    }
    return v1.third < v2.third;
  });
  for (auto i : v) {
    std::cout << i.third << '\n';
  }
}