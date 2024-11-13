#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
  std::string text;
  std::map<std::string, std::map<std::string, int64_t>> dict;
  std::vector<std::pair<std::string, std::vector<std::pair<std::string, int64_t>>>> vec;
  std::fstream file("input.txt");
  file.open("input.txt");
  char a;
  while (file.get(a)) {
    text += a;
  }
  file.close();
  file.open("input.txt");
  std::string product, name;
  int64_t quantity;
  while (file >> name) {
    file >> product >> quantity;
    dict[name][product] += quantity;
  }
  for (auto i : dict) {
    name = i.first;
    std::vector<std::pair<std::string, int64_t>> vector_of_products;
    for (auto j : i.second) {
      vector_of_products.emplace_back(j);
    }
    vec.emplace_back(std::make_pair(name, vector_of_products));
  }
  std::sort(vec.begin(), vec.end());
  for (auto i : vec) {
    std::sort(i.second.begin(), i.second.end());
  }
  for (auto i : vec) {
    std::cout << i.first << ':' << '\n';
    for (auto j : i.second) {
      std::cout << j.first << ' ' << j.second << '\n';
    }
  }
}