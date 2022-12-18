#include <fmt/format.h>
#include <iostream>
#include <vector>

int main() {

  std::string str;
  using pii = std::pair<int, int>;
  int ansI = 0;
  int ansII = 0;
  while (std::cin >> str) {
    std::pair<int, int> a, b;
    if (std::sscanf(str.c_str(), "%d-%d,%d-%d", &a.first, &a.second, &b.first,
                    &b.second) == 4) {
      // fmt::print("pair read:({},{}) and {}\n", a.first, a.second, b.first);
    } else {
      fmt::print("something wrong.\n");
    }

    if (a.first < b.first || (a.first == b.first && a.second > b.second)) {
      std::swap(a, b);
    }

    if (a.first >= b.first && b.second >= a.second) {
      ansI++;
    }

    if (a.first > b.first) {
      std::swap(a, b);
    }

    if (a.second >= b.first)
      ansII++;
  }
  fmt::print("PartI :{}\n", ansI);
  fmt::print("PartII :{}\n", ansII);
}
