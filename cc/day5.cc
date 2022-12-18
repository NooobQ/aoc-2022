#include <cstdio>
#include <deque>
#include <fmt/format.h>
#include <iostream>
#include <memory>
#include <queue>
#include <regex>
#include <set>
#include <vector>

class cargo {
public:
  void put_stack(int idx, int crate) {
    cargo_stack[idx].push_back(crate);
    fmt::print("put {} on stack {}\n", static_cast<char>(crate), idx);
  }
  void mv(int n, int src, int dst) {
    while (n--) {
      auto x = cargo_stack[src].front();
      cargo_stack[src].pop_front();
      cargo_stack[dst].push_front(x);
      fmt::print("moving {} from {} to {}\n", static_cast<char>(x), src, dst);
    }
  }
  std::string getRes() {
    std::string res;
    for (int i = 1; i <= n; i++) {
      if (cargo_stack.empty()) {
        fmt::print("Error\n");
      }
      res.push_back(static_cast<char>(cargo_stack[i].front()));
    }
    return res;
  }
  cargo() : cargo_stack(0), n(0) {}
  cargo(int n) : cargo_stack(n + 1, std::deque<int>()), n(n) {}

private:
  std::vector<std::deque<int>> cargo_stack;
  int n;
};
void mv(int n, int src, int dst);
int main() {
  int a;
  std::string str;
  auto calc = [](int leng) { return (leng + 1) / 4; };
  auto flag = false;
  auto len = 0;
  std::unique_ptr<cargo> pc = nullptr;
  std::unique_ptr<cargo> px = nullptr;
  while (std::getline(std::cin, str)) {
    if (!str.length()) {
      flag = true;
      continue;
    }
    if (!flag) {
      if (pc == nullptr) {
        len = calc(str.length());
        fmt::print("len={}\n", len);
        pc = std::make_unique<cargo>(len);
        px = std::make_unique<cargo>(len);
      }

      for (int i = 0; i < len; i++) {
        auto x = i * 4 + 1;
        if (x < str.length() && str[x] != ' ') {
          fmt::print("x={}, ch={}\n", x, str[x]);
          pc->put_stack(i + 1, str[x]);
          px->put_stack(i + 1, str[x]);
        }
      }
    } else {
      int num, src, dst;
      sscanf(str.c_str(), "move %d from %d to %d", &num, &src, &dst);
      fmt::print("num={}, x={}, y={}\n", num, src, dst);
      pc->mv(num, src, dst);
      px->mv(num, src, 0);
      px->mv(num, 0, dst);
    }
  }
  fmt::print("PartI ans= {}\n", pc->getRes());
  fmt::print("PartII ans= {}\n", px->getRes());
  return 0;
}
