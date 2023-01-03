// day11 Part 2
#include <algorithm>
#include <cstdio>
#include <fmt/format.h>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

struct monkey {
  std::vector<int> item;
  std::vector<std::vector<int>> item_mod;
  std::function<int(int)> operation;
  int div_;
  int monkey_a;
  int monkey_b;
  int inspect_times;

  monkey(std::vector<int> &&vec, std::function<int(int)> funca, int div, int m1,
         int m2)
      : item(std::move(vec)), operation(funca), div_(div), monkey_a(m1),
        monkey_b(m2), inspect_times(0) {}
};

int main() {
  std::vector<monkey> monkeys;
  auto general_test = [&](int x, int div, int m1, int m2, int round) {
    // x /= 3;
    if (x % div == 0) {
      monkeys[m1].item.push_back(x);
    } else {
      monkeys[m2].item.push_back(x);
    }
  };
  using std::placeholders::_1;
  using std::placeholders::_2;
  // Test Monkey:
  // monkeys.push_back(monkey(
  //     {79, 98}, [](int x) { return x * 19; }, 23, 2, 3));
  // monkeys.push_back(monkey(
  //     {54, 65, 75, 74}, [](int x) { return x + 6; }, 19, 2, 0));
  // monkeys.push_back(monkey(
  //     {79, 60, 97}, [](int x) { return x * x; }, 13, 1, 3));
  // monkeys.push_back(monkey(
  //     {74}, [](int x) { return x + 3; }, 17, 0, 1));

  // Monkey 0
  monkeys.push_back(monkey(
      {89, 74}, [](int x) { return x * 5; }, 17, 4, 7));
  // Monkey 1
  monkeys.push_back(monkey(
      {75, 69, 87, 57, 84, 90, 66, 50}, [](int x) { return x + 3; }, 7, 3, 2));
  // Monkey 2
  monkeys.push_back(monkey(
      {55}, [](int x) { return x + 7; }, 13, 0, 7));
  // Monkey 3
  monkeys.push_back(monkey(
      {69, 82, 69, 56, 68}, [](int x) { return x + 5; }, 2, 0, 2));
  // Monkey 4
  monkeys.push_back(monkey(
      {72, 97, 50}, [](int x) { return x + 2; }, 19, 6, 5));
  // Monkey 5
  monkeys.push_back(monkey(
      {90, 84, 56, 92, 91, 91}, [](int x) { return x * 19; }, 3, 6, 1));
  // Monkey 6
  monkeys.push_back(monkey(
      {63, 93, 55, 53}, [](int x) { return x * x; }, 5, 3, 1));
  // Monkey 7
  monkeys.push_back(monkey(
      {50, 61, 52, 58, 86, 68, 97}, [](int x) { return x + 4; }, 11, 5, 4));

  int n = monkeys.size();
  for (int i = 0; i < n; i++) {
    for (auto &item : monkeys[i].item) {
      std::vector<int> tmp;
      for (int j = 0; j < n; j++) {
        tmp.push_back(item % monkeys[j].div_);
      }
      monkeys[i].item_mod.push_back(tmp);
    }
  }

  for (int round = 0; round < 10000; round++) {
    for (int x = 0; x < n; x++) {
      auto &mon = monkeys[x];
      auto vec = std::move(mon.item_mod);
      mon.item_mod = std::vector<std::vector<int>>();
      mon.inspect_times += vec.size();
      for (auto &item : vec) {
        // 1 item is a vector contains all div msg.
        for (int i = 0; i < n; i++) {
          item[i] %= monkeys[i].div_; // useless?
          item[i] = mon.operation(item[i]) % monkeys[i].div_;
        }
        if (item[x] % monkeys[x].div_ == 0) {
          monkeys[mon.monkey_a].item_mod.push_back(item);
        } else {
          monkeys[mon.monkey_b].item_mod.push_back(item);
        }
      }
      // auto vec = std::move(mon.item);
      // mon.inspect_times += vec.size();
      // mon.item = std::vector<int>();
      // for (auto item : vec) {
      //   auto x = mon.operation(item);
      // }
    }

    if ((round + 1) % 1000 == 0 || round == 0 || round == 19) {
      fmt::print("Round #{}\n", round + 1);
      int i = 0;
      for (const auto &mon : monkeys) {
        fmt::print("Monkey #{} inspect_times: {}\n", i++, mon.inspect_times);
      }
    }
  }
  std::vector<long long> vec;
  for (auto &mon : monkeys) {
    vec.push_back(mon.inspect_times);
  }
  std::sort(vec.begin(), vec.end(), std::greater<long long>());
  fmt::print("Part II ans = {}\n", vec[0] * vec[1]);
}
