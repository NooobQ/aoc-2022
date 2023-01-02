#include <climits>
#include <fmt/format.h>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

void solve(std::vector<std::vector<int>> &);
void solve2(std::vector<std::vector<int>> &);
int main() {
  std::vector<std::vector<int>> matrix;

  std::string str;
  auto cnt = 0U;
  while (std::getline(std::cin, str)) {
    auto len = str.length();
    matrix.push_back(std::vector<int>());
    for (auto ch : str) {
      matrix[cnt].push_back(ch - '0');
    }
    cnt++;
  }

  auto m = matrix[0].size();
  auto n = cnt;

  fmt::print("m = {}, n = {}", m, n);
  solve2(matrix);
}
void solve2(std::vector<std::vector<int>> &matrix) {
  auto m = matrix[0].size();
  auto n = matrix.size();

  std::vector<std::vector<int>> res1(n, std::vector<int>(m, 0));
  std::vector<std::vector<int>> res2(res1), res3(res1), res4(res1);
  int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  using pii = std::pair<int, int>;
  // d1 -- nest loop direction, d2 -- outside loop direction
  auto func = [&](std::vector<std::vector<int>> &res, int startx, int starty,
                  int d1, int d2) {
    for (int i = 0; i < n; i++) {
      std::stack<pii> s;
      // build a monolitic stack the bottom always greater than the top
      for (int j = 0; j < n; j++) {
        auto x = startx + j * dir[d1][0] + i * dir[d2][0];
        auto y = starty + j * dir[d1][1] + i * dir[d2][1];
        // fmt::print("x = {}, y = {}\n", x, y);
        while (!s.empty() && s.top().first < matrix[x][y]) {
          s.pop();
        }
        res[x][y] = s.empty() ? j : j - s.top().second;
        s.push({matrix[x][y], j});
      }
    }
  };
  func(res1, 0, 0, 0, 1);
  func(res2, n - 1, 0, 2, 1);
  func(res3, 0, 0, 1, 0);
  func(res4, 0, n - 1, 3, 0);
  fmt::print("\n");
  int res = INT_MIN;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      res = std::max(res, res1[i][j] * res2[i][j] * res3[i][j] * res4[i][j]);
    }
  }
  fmt::print("part2 res={}\n", res);
}

// shitty copy-paste mode
void solve(std::vector<std::vector<int>> &matrix) {
  auto m = matrix[0].size();
  auto n = matrix.size();

  std::vector<std::vector<int>> res(n, std::vector<int>(m, 0));
  std::vector<int> rtmp(m, -1), ctmp(n, -1);
  for (auto i = 0U; i < n; i++) {
    for (auto j = 0U; j < m; j++) {
      if (matrix[i][j] > rtmp[j]) {
        rtmp[j] = matrix[i][j];
        res[i][j] = 1;
      }
    }
  }
  fmt::print("\n");
  for (auto &foo : rtmp) {
    foo = -1;
  }

  for (auto i = n - 1; i < n; i--) {
    for (auto j = 0U; j < m; j++) {
      if (matrix[i][j] > rtmp[j]) {
        rtmp[j] = matrix[i][j];
        res[i][j] = 1;
      }
    }
  }

  for (auto j = 0U; j < m; j++) {
    for (auto i = 0U; i < n; i++) {
      if (matrix[i][j] > ctmp[i]) {
        ctmp[i] = matrix[i][j];
        res[i][j] = 1;
      }
    }
  }
  for (auto &foo : ctmp) {
    foo = -1;
  }
  for (auto j = m - 1; j < m; j--) {
    for (auto i = 0U; i < n; i++) {
      if (matrix[i][j] > ctmp[i]) {
        ctmp[i] = matrix[i][j];
        res[i][j] = 1;
      }
    }
  }

  int ans = 0;
  for (auto vec : res) {
    for (auto cell : vec) {
      std::cout << cell;
      ans += cell;
    }
    std::cout << '\n';
  }
  fmt::print("PartI ans: {}\n", ans);
}
