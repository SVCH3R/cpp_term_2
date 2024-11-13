#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>

int main() {
  std::string text, word;
  std::map<std::string, int> dict;
  std::fstream file("input.txt");
  file.open("input.txt");
  char a;
  while (file.get(a)) {
    text += a;
  }
  file.close();
  file.open("input.txt");
  while (file >> word) {
    ++dict[word];
  }
  std::vector<std::pair<std::string, int>> vec;
  for (auto i : dict) {
    vec.emplace_back(i);
  }
  std::sort(vec.begin(), vec.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
    if (a.second != b.second) {
      return a.second > b.second;
    }
    return b.first > a.first;
  });
  for (auto i = vec.begin(); i != vec.end(); ++i) {
    std::cout << i->first << '\n';
  }
} 