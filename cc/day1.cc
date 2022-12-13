#include <fmt/format.h>
#include <iostream>
#include <set>

int main() {
  int a = 0;
  std::string str;
  int cur_calory_acc = 0;
  int ans_partI = 0, ans_partII = 0;
  std::multiset<int> calories;
  while (std::getline(std::cin, str)) {
    if (str.length()) {
      cur_calory_acc += stoi(str);
    } else {
      calories.insert(cur_calory_acc);
      cur_calory_acc = 0;
    }
  }
  if (cur_calory_acc) {
    calories.insert(cur_calory_acc);
  }

  auto iter = calories.rbegin();
  ans_partI = *iter;
  for (int i = 0; i < 3 && iter != calories.rend(); i++, iter++) {
    ans_partII += *iter;
  }

  fmt::print("part I ans={}\n", ans_partI);
  fmt::print("part II ans={}\n", ans_partII);
}
