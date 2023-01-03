// day11 Part 1.
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
  std::function<void(int, int)> tests;
  int inspect_times{0};

  monkey(std::vector<int> &&vec, std::function<int(int)> funca,
         std::function<void(int, int)> funcb)
      : item(std::move(vec)), operation(funca), tests(funcb), inspect_times(0) {
  }
};

int main() {
  std::vector<monkey> monkeys;
  auto general_test = [&](int x, int div, int m1, int m2, int round) {
    x /= 3;
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
  //     {79, 98}, [](int x) { return x * 19; },
  //     std::bind(general_test, _1, 23, 2, 3, _2)));
  // monkeys.push_back(monkey(
  //     {54, 65, 75, 74}, [](int x) { return x + 6; },
  //     std::bind(general_test, _1, 19, 2, 0, _2)));
  // monkeys.push_back(monkey(
  //     {79, 60, 97}, [](int x) { return x * x; },
  //     std::bind(general_test, _1, 13, 1, 3, _2)));
  // monkeys.push_back(monkey(
  //     {74}, [](int x) { return x + 3; },
  //     std::bind(general_test, _1, 17, 0, 1, _2)));

  // Monkey 0
  monkeys.push_back(monkey(
      {89, 74}, [](int x) { return x * 5; },
      std::bind(general_test, _1, 17, 4, 7, _2)));
  // Monkey 1
  monkeys.push_back(monkey(
      {75, 69, 87, 57, 84, 90, 66, 50}, [](int x) { return x + 3; },
      std::bind(general_test, _1, 7, 3, 2, _2)));
  // Monkey 2
  monkeys.push_back(monkey(
      {55}, [](int x) { return x + 7; },
      std::bind(general_test, _1, 13, 0, 7, _2)));
  // Monkey 3
  monkeys.push_back(monkey(
      {69, 82, 69, 56, 68}, [](int x) { return x + 5; },
      std::bind(general_test, _1, 2, 0, 2, _2)));
  // Monkey 4
  monkeys.push_back(monkey(
      {72, 97, 50}, [](int x) { return x + 2; },
      std::bind(general_test, _1, 19, 6, 5, _2)));
  // Monkey 5
  monkeys.push_back(monkey(
      {90, 84, 56, 92, 91, 91}, [](int x) { return x * 19; },
      std::bind(general_test, _1, 3, 6, 1, _2)));
  // Monkey 6
  monkeys.push_back(monkey(
      {63, 93, 55, 53}, [](int x) { return x * x; },
      std::bind(general_test, _1, 5, 3, 1, _2)));
  // Monkey 7
  monkeys.push_back(monkey(
      {50, 61, 52, 58, 86, 68, 97}, [](int x) { return x + 4; },
      std::bind(general_test, _1, 11, 5, 4, _2)));

  for (int round = 0; round < 20; round++) {
    int i = 0;
    for (auto &mon : monkeys) {
      auto vec = std::move(mon.item);
      mon.inspect_times += vec.size();
      mon.item = std::vector<int>();
      for (auto item : vec) {
        auto x = mon.operation(item);
        mon.tests(x, round);
      }
    }

    fmt::print("Round {}\n", round);
    i = 1;
    for (const auto &mon : monkeys) {
      fmt::print("Monkey #{}'s Item: ", i++);
      for (auto item : mon.item) {
        fmt::print("{}, ", item);
      }
      fmt::print("\n");
      fmt::print("inspect_times: {}\n", mon.inspect_times);
    }
  }

  std::vector<int> vec;
  for (auto &mon : monkeys) {
    vec.push_back(mon.inspect_times);
  }
  std::sort(vec.begin(), vec.end(), std::greater<long long>());
  fmt::print("Part I ans = {}\n", vec[0] * vec[1]);
}
