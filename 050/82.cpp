#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Node {
  int x, y;
};

struct Edge {
  Node from, to;
  int value;
};

class Compare {
public:
  bool operator()(Edge a, Edge b) { return a.value > b.value; }
};

void fill_in_line(std::string &line, std::vector<int> &arr, int start_id = 0) {

  int cur_id = line.find(','), prev_id = 0;
  int insert_id = start_id;

  while (cur_id != std::string::npos) {
    arr[insert_id] = std::stoi(line.substr(prev_id, cur_id - prev_id));
    insert_id++;

    prev_id = cur_id + 1;
    cur_id = line.find(',', prev_id);
  }
  arr[insert_id] = std::stoi(line.substr(prev_id));
}

int main() {
  constexpr const int min_size = 128;
  constexpr const int INF = 1 << 26;
  std::vector<std::vector<int>> matrix(min_size, std::vector<int>(min_size, INF));
  std::vector<std::vector<int>> used(min_size, std::vector<int>(min_size, INF));

  const std::vector<int> neighX = {0, 1, 0}, neighY = {-1, 0, 1};

  std::priority_queue<Edge, std::vector<Edge>, Compare> heap;

  std::fstream file;
  file.open("82.txt", std::ios_base::in);
  if (!file) {
    std::cout << "Error reading file\n";
    return 1;
  }

  std::string line;
  int N = 0;
  while (file >> line) {
    fill_in_line(line, matrix[N], 1);
    heap.push({{0, 0}, {1, N}, matrix[N][1]});
    N++;
  }

  used[0][0] = 0;

  while (!heap.empty()) {
    auto cur = heap.top();
    heap.pop();

    // std::cout << std::format("Maybe?: ({}, {}) -> ({},{}), val={}\n",
    //                          cur.from.x, cur.from.y, cur.to.x, cur.to.y,
    //                          cur.value);

    // std::cout << std::format("Used: {} -> {} + {}\n", used[cur.to.y][cur.to.x],
    //                          used[cur.from.y][cur.from.x], cur.value);
    //
    if (used[cur.to.y][cur.to.x] > used[cur.from.y][cur.from.x] + cur.value) {

      // std::cout << std::format("YES: ({}, {}) -> ({},{}), val={}\n", cur.from.x,
      //                          cur.from.y, cur.to.x, cur.to.y, cur.value);

      used[cur.to.y][cur.to.x] = used[cur.from.y][cur.from.x] + cur.value;

      for (int i = 0; i < neighX.size(); i++) {
        int nextX = cur.to.x + neighX[i];
        int nextY = cur.to.y + neighY[i];

        if (nextY == N || nextY < 0)
          continue;

        if (nextX == N + 1) {
           heap.push(
              {{cur.to.x, cur.to.y}, {nextX, 0}, 0});
        }
        else if (used[nextY][nextX] >
            used[cur.to.y][cur.to.x] + matrix[nextY][nextX]) {
          heap.push(
              {{cur.to.x, cur.to.y}, {nextX, nextY}, matrix[nextY][nextX]});
        }
      }
    }
  }
  
  // for(int i = 0; i < N; i ++){
  //   for(int j = 0; j <= N + 1; j++){
  //     std::cout << used[i][j] << "\t";
  //   }
  //   std::cout << std::endl;
  // }
  std::cout << used[0][N+1] << std::endl;
  
  return 0;
}
