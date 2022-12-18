#include <fmt/format.h>
#include <iostream>
#include <set>
#include <vector>

int calc_priority(char ch) {
  if ('a' <= ch && ch <= 'z')
    return ch + 1 - 'a';
  return ch + 27 - 'A';
}
int main() {

  std::string str;

  int ansI = 0;
  int ansII = 0;
  int n = 0;
  using vi = std::vector<int>;
  // change to single vector + init + bitand
  std::vector<vi> groups(3, vi(2 * 26 + 1, 0));
  while (std::cin >> str) {
    std::set<char> chset;
    auto iter = str.begin();

    for (auto &foo : groups[n % 3])
      foo = 0;
    for (auto ch : str) {
      groups[n % 3][calc_priority(ch)] = 1;
    }
    if (n % 3 == 2) {
      for (int i = 1; i <= 52; i++) {
        if (groups[0][i] && groups[1][i] && groups[2][i]) {
          // fmt::print("i = {}\n", i);
          ansII += i;
        }
      }
    }
    n++;

    // use split to split the string then calc the diff of both set
    while (std::distance(str.begin(), iter) < str.length() / 2) {
      chset.insert(*iter);
      // fmt::print("Insert {}\n", *iter);
      iter++;
    }

    while (iter != str.end()) {
      if (chset.count(*iter)) {
        // fmt::print("Find Dup char {}\n", *iter);
        ansI += calc_priority(*iter);
        break;
      }
      iter++;
    }
  }
  fmt::print("PartI result = {}\n", ansI);
  fmt::print("PartII result = {}\n", ansII);
}
