#include <iostream>
#include <string>
#include <unordered_map>
#include <any>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, cmd;
  std::cin >> n;
  std::string name;
  std::unordered_map<std::string, int> bank;
  for (int i = 0; i < n; ++i) {
    std::cin >> cmd >> name;
    if (cmd == 1) {
      std::cin >> cmd;
      bank[name] += cmd;
    } else {
      if (bank.count(name)) {
        std::cout << bank[name] << '\n';
      } else {
        std::cout << "ERROR" << '\n';
      }
    }
  }
}