#include <iostream>
#include <queue>
class command {
public:
  std::string Action;
  int V;
  int T;
  command(std::string action, int v) : Action(action), V(v) {
    if (action == "addx") {
      this->T = 2;
    } else {
      this->T = 1;
    }
  };
  command() : Action(""), V(0){};
};

int main() {
  std::string action;
  int reg_x = 1;
  int v;

  int ans_1 = 0;
  auto solve_1 = [&ans_1](int x) { ans_1 += x; };

  std::queue<command> q;
  while (std::cin >> action) {
    if (action == "addx") {
      std::cin >> v;
    }
    command cur_cmd(action, v);
    q.push(cur_cmd);
  }

  int exec_cycle = 0;
  std::string crt_image;
  while (!q.empty()) {
    auto cur = q.front();
    q.pop();
    while (cur.T) {
      cur.T--;
      exec_cycle++;
      // std::cout << reg_x << ' ' << exec_cycle << "\n";
      if ((exec_cycle - 20) % 40 == 0) {
        solve_1(reg_x * exec_cycle);
      }
      if (exec_cycle <= 240) {
        auto x = (exec_cycle - 1) % 40;

        // auto y = exec_cycle / 40;
        if (reg_x - 1 <= x && x <= reg_x + 1) {
          crt_image += '#';
        } else {
          crt_image += '.';
        }
      }
      if (cur.Action == "addx" && cur.T == 0) {
        reg_x += cur.V;
      }
    }
  }
  std::cout << ans_1 << '\n';
  std::cout << "CRT_IMG:\n";
  for (int i = 0; i < 6; i++) {
    std::cout << crt_image.substr(i * 40, 40) << '\n';
  }
  return 0;
}
