#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

void add_to(int t, int i, std::unordered_map<int, std::vector<bool>> &map) {
  if (t % 100 < 10) {
    return;
  }
  if (map.find(t) == map.end()) {
    map.emplace(t, std::vector<bool>(6, 0));
  }
  map[t][i] = true;
}

int main() {

  std::unordered_map<int, std::vector<bool>> typeBM_by_num;
  for (int i = 0; i <= 1000; i++) {
    int t = i * (i + 1) / 2;
    if (t > 999 & t < 10000)
      add_to(t, 0, typeBM_by_num);

    int s = i * i;
    if (s > 999 && s < 10000)
      add_to(s, 1, typeBM_by_num);

    int p = i * (3 * i - 1) / 2;
    if (p > 999 && p < 10000)
      add_to(p, 2, typeBM_by_num);

    int h6 = i * (2 * i - 1);
    if (h6 > 999 && h6 < 10000)
      add_to(h6, 3, typeBM_by_num);

    int h7 = i * (5 * i - 3) / 2;
    if (h7 > 999 && h7 < 10000)
      add_to(h7, 4, typeBM_by_num);

    int o = i * (3 * i - 2);
    if (o > 999 && o < 10000)
      add_to(o, 5, typeBM_by_num);
  }

  std::unordered_map<int, std::set<int>> graph;
  for (auto &[key, v] : typeBM_by_num) {
    graph[key] = {};
    for (auto &[key2, v2] : typeBM_by_num) {
      if (key2 / 100 == key % 100) {
        graph[key].insert(key2);
      }
    }
  }
  std::erase_if(graph, [](const auto &a) { return a.second.empty(); });

  std::set<int> used = {};
  for (auto &[a1, v] : graph) {
    used.insert(a1);
    for (auto a2 : v) {
      auto a2f = used.insert(a2);
      if (!a2f.second)
        continue;
      for (auto a3 : graph[a2]) {
        auto a3f = used.insert(a3);
        if (!a3f.second)
          continue;
        for (auto a4 : graph[a3]) {
          auto a4f = used.insert(a4);
          if (!a4f.second)
            continue;
          for (auto a5 : graph[a4]) {
            auto a5f = used.insert(a5);
            if (!a5f.second)
              continue;
            for (auto a6 : graph[a5]) {
              if (graph[a6].find(a1) == graph[a6].end())
                continue;

              auto a6f = used.insert(a6);
              if (!a6f.second)
                continue;

              std::vector<int> perm(used.begin(), used.end());
              bool is_next = true, is_ans = false;
              // std::cout << "Testing numbers: " << perm.size() << " (" << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5
              //           << " " << a6 << ")\n";
              while (is_next) {
                bool flag = true;
                for (int i = 0; i < 6; i++) {
                  flag = flag && typeBM_by_num[perm[i]][i];
                }
                if (flag) {
                  is_ans = true;
                  break;
                }
                is_next = std::next_permutation(perm.begin(), perm.end());
              }
              if (is_ans) {
                
                for (auto n : used) {
                  std::cout << n << ": ";
                  for (bool b : typeBM_by_num[n])
                    std::cout << b << " ";
                  std::cout << std::endl;
                }
                std::cout << a1 << " " << a2 << " " << a3 << " " << a4 << " "
                          << a5 << " " << a6 << std::endl;
                std::cout << (a1 + a2 + a3 + a4 + a5 + a6) << "\n";
                return 0;
              }
              used.erase(a6);
            }
            used.erase(a5);
          }
          used.erase(a4);
        }
        used.erase(a3);
      }
      used.erase(a2);
    }
    used.erase(a1);
  }

  return 0;
}
