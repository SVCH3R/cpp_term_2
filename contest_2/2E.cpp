#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::string word1, word2;
  std::unordered_map<std::string, std::string> synonyms;
  for (int i = 0; i < n; ++i) {
    std::cin >> word1 >> word2;
    synonyms[word1] = word2;
    synonyms[word2] = word1;
  }
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    std::cin >> word1;
    std::cout << synonyms[word1] << '\n';
  }
}
