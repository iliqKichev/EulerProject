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

  const std::vector<int> neighX = {0, 1, 0, -1}, neighY = {-1, 0, 1, 0};

  std::priority_queue<Edge, std::vector<Edge>, Compare> heap;

  std::fstream file;
  file.open("83.txt", std::ios_base::in);
  if (!file) {
    std::cout << "Error reading file\n";
    return 1;
  }

  std::string line;
  int N = 0;
  while (file >> line) {
    fill_in_line(line, matrix[N]);
    N++;
  }

  heap.push({{0, 0}, {1, 0}, matrix[0][1]});
  heap.push({{0, 0}, {0, 1}, matrix[1][0]});
  used[0][0] = matrix[0][0];

  while (!heap.empty()) {
    auto cur = heap.top();
    heap.pop();

    if (used[cur.to.y][cur.to.x] > used[cur.from.y][cur.from.x] + cur.value) {


      used[cur.to.y][cur.to.x] = used[cur.from.y][cur.from.x] + cur.value;

      for (int i = 0; i < neighX.size(); i++) {
        int nextX = cur.to.x + neighX[i];
        int nextY = cur.to.y + neighY[i];

        if (nextY == N || nextY < 0)
          continue;

        if (nextX == N || nextX < 0) {
          continue;
        }

        if (used[nextY][nextX] >
            used[cur.to.y][cur.to.x] + matrix[nextY][nextX]) {
          heap.push(
              {{cur.to.x, cur.to.y}, {nextX, nextY}, matrix[nextY][nextX]});
        }
      }
    }
  }
  
  std::cout << used[N-1][N-1] << std::endl;
  
  return 0;
}
