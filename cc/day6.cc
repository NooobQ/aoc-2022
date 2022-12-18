#include <fmt/format.h>
#include <iostream>
#include <set>
#include <vector>

int solve(std::string str, int n) {
  std::vector<int> alpha_table(256, 0);
  for (int i = 0; i < str.length(); i++) {
    auto idx = static_cast<int>(str[i]);
    alpha_table[idx]++;
    if (i < n - 1)
      continue;
    if (i >= n) {
      auto prev = static_cast<int>(str[i - n]);
      alpha_table[prev] -= 1;
    }
    auto flag = true;
    for (int j = 0; j < n; j++) {
      auto x = static_cast<int>(str[i - j]);
      if (alpha_table[x] > 1)
        flag = false;
    }
    if (flag) {
      fmt::print("Part solve({}) ans={}\n", n, i + 1);
      return i + 1;
    }
  }
  fmt::print("something wrong\n");
  return -1;
}
int main() {
  std::string str;
  auto resI = 0;
  while (std::cin >> str) {
    solve(str, 4);
    solve(str, 14);
  }
}
