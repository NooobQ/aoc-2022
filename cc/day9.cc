#include <fmt/format.h>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>

int main() {

  char command;
  int argx;
  int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  std::map<char, int> dict;
  using pii = std::pair<int, int>;
  std::set<pii> point_set1;
  std::set<pii> point_set2;
  // std::unordered_set<pii> point_set;
  dict['R'] = 0;
  dict['U'] = 1;
  dict['L'] = 2;
  dict['D'] = 3;

  std::vector<pii> shortsnap(2, {0, 0});
  std::vector<pii> snap(10, {0, 0});
  int diag[4][2] = {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
  while (std::cin >> command >> argx) {
    int d = dict[command];
    auto func = [&dir, d, &diag](pii &h, pii &t, bool flag) {
      auto &hx = h.first;
      auto &hy = h.second;
      auto &tx = t.first;
      auto &ty = t.second;
      if (flag) {
        hx += dir[d][0];
        hy += dir[d][1];
      }
      if (std::abs(hx - tx) + std::abs(hy - ty) > 2) {
        for (int i = 0; i < 4; i++) {
          if (std::abs(tx + diag[i][0] - hx) <= 1 &&
              std::abs(ty + diag[i][1] - hy) <= 1) {
            tx += diag[i][0];
            ty += diag[i][1];
            break;
          }
        }
      } else {
        if (std::abs(hx - tx) == 2 || std::abs(hy - ty) == 2) {
          tx += (hx - tx) / 2;
          ty += (hy - ty) / 2;
        }
      }
    };

    auto solve1 = [&]() {
      for (int i = 0; i < argx; i++) {
        func(shortsnap[0], shortsnap[1], true);
        point_set1.insert(shortsnap[1]);
      }
    };
    solve1();

    auto solve2 = [&]() {
      for (int i = 0; i < argx; i++) {
        for (int j = 0; j < 9; j++) {
          func(snap[j], snap[j + 1], j == 0);
        }
        point_set2.insert(snap[9]);
      }
    };
    solve2();
  }
  fmt::print("partI ans = {}\n", point_set1.size());
  fmt::print("partII ans = {}\n", point_set2.size());
}
