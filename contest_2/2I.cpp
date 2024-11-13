#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
  std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> q;
  int64_t n, input, sum;
  int64_t fee = 0;
  std::cin >> n;
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> input;
    q.emplace(input);
  }
  while (q.size() > 1) {
    sum = q.top();
    q.pop();
    sum += q.top();
    q.pop();
    fee += sum;
    q.emplace(sum);
  }
  std::cout << fee * 0.05;
}