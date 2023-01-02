#include <cctype>
#include <climits>
#include <fmt/format.h>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

class file;

std::shared_ptr<file> work_dir, root;
const std::string LS("ls"), CD("cd");

class file {
public:
  file(std::string _path, bool _isDir, int size)
      : path(_path), isDir(_isDir), fileSize(size) {}
  std::shared_ptr<file> getParent() { return this->parent.lock(); }
  // TO-DO: mod to enable shared from this
  void insert(std::string filename, bool isDir, int filesize) {
    subDir.push_back(std::make_shared<file>(filename, isDir, filesize));
    for (auto child : subDir) {
      child->parent = work_dir;
    }
  }
  void output() { pwd(0); }
  void pwd(int depth) {
    for (int i = 0; i < depth; i++)
      fmt::print("..");
    fmt::print("curDir={}, isDir={}, size={}\n", path, isDir, fileSize);
    for (auto p : subDir) {
      p->pwd(depth + 1);
    }
  }
  int calc() {
    if (!isDir) {
      return fileSize;
    }

    auto total = 0;
    for (auto child : subDir) {
      total += child->calc();
    }
    return fileSize = total;
  }
  std::shared_ptr<file> getDir(std::string path) {
    for (auto child : subDir) {
      if (child->path == path)
        return child;
    }
    return nullptr;
  }
  std::string getName() { return path; }

  // ParI
  int getResI() {
    auto res = 0;
    if (fileSize < 100000) {
      res += fileSize;
    }
    for (auto child : subDir) {
      if (child->isDir) {
        res += child->getResI();
      }
    }
    return res;
  }

  // PartII
  int getResII() {
    const int TOTALSIZE = 70000000;
    const int SPACENEED = 30000000;
    int free_space = TOTALSIZE - fileSize;
    std::queue<std::shared_ptr<file>> q;
    for (auto child : subDir) {
      if (child->isDir)
        q.push(child);
    }
    auto res = fileSize;
    while (!q.empty()) {
      auto cur = q.front();
      q.pop();
      if (free_space + cur->fileSize > SPACENEED) {
        res = std::min(res, cur->fileSize);
      }
      for (auto child : cur->subDir) {
        if (child->isDir)
          q.push(child);
      }
    }

    return res;
  }

private:
  std::vector<std::shared_ptr<file>> subDir;
  std::string path;
  std::weak_ptr<file> parent;
  int fileSize;
  bool isDir;
};
void cd(std::string path) {
  if (path == "/") {
    work_dir = root;
    return;
  }
  if (path == "..") {
    work_dir = work_dir->getParent();
    return;
  }
  work_dir = work_dir->getDir(path);
}
int main() {
  std::string str;
  root = std::make_shared<file>("/", true, 0);
  while (std::getline(std::cin, str)) {
    if (!str.empty() && str[0] == '$') {
      std::string path;
      fmt::print("detected cmd: {}\n", str);
      std::string cmd = str.substr(2, 2);
      fmt::print("cmd = {}, path = {}\n", cmd, path);
      if (cmd == CD) {
        std::stringstream s(str);
        std::string blank_1, blank_2, path;
        s >> blank_1 >> blank_2 >> path;
        fmt::print("$={}, cd={}, path={}\n", blank_1, blank_2, path);
        cd(path);
        fmt::print("change dir to {}\n", work_dir->getName());
      } else {
      }
    } else {
      // receive ls result
      int file_size;
      std::string file;
      std::stringstream s(str);
      if (std::isdigit(str[0])) {
        int size;
        s >> size >> file;
        fmt::print("get size={}, path={}\n", size, file);
        work_dir->insert(file, false, size);
      } else {
        std::string blank_1;
        s >> blank_1 >> file;
        fmt::print("get dir={}, path={}\n", blank_1, file);
        work_dir->insert(file, true, 0);
      }
    }
  }
  root->calc();
  root->output();
  fmt::print("PartI ans={}\n", root->getResI());
  fmt::print("PartII ans={}\n", root->getResII());
}
