#include <fmt/format.h>
#include <iostream>

enum shape {
  ROCK = 1,
  PAPER = 2,
  SCISSORS = 3,
};

int solve1(int play, int opp) {
  // Case Draw
  if (play == opp)
    return 3;
  // Case Win
  if (play - opp == 1 || (play == ROCK && opp == SCISSORS))
    return 6;
  // Case Lose
  return 0;
}

int solve2(int opp, int sit) {
  int win_score = (sit - 1) * 3;
  int res = 0;
  switch (sit) {
  case 1: // Case Lose
    res = opp - 1;
    break;
  case 2: // Case Draw
    res = opp;
    break;
  case 3: // Case Win
    res = opp + 1;
    break;
  }
  // Out of range MOD
  if (res % 4 == 0) {
    res = (res + 3) % 6;
  }
  // if (res == 0)
  //   res = 3;
  // if (res == 4)
  //   res = 1;
  return res + win_score;
}

int main() {
  char opp, player;
  int ans_partI = 0;
  int ans_partII = 0;
  while (std::cin >> opp >> player) {
    int x, y;
    x = opp - 'A' + 1;
    y = player - 'X' + 1;
    ans_partI += solve1(y, x) + y;
    ans_partII += solve2(x, y);
    // fmt::print("playing{},{}, win={}\n", x, y, score(y, x));
    // fmt::print("playing{},{}, tmpscore={}\n", x, y, solve2(x, y));
  }
  fmt::print("partI:{}\n", ans_partI);
  fmt::print("partII:{}\n", ans_partII);
}
