#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

bool is_prime(int i) {
  for (int j = 2; j * j <= i; j++) {
    if (i % j == 0)
      return false;
  }
  return true;
}

void bron_kerbosch(const std::set<int> &current_clique,
                   std::set<int> candidates, std::set<int> processed_vertices,
                   std::vector<std::set<int>> graph,
                   std::vector<std::vector<int>> &cliques) {

  if (candidates.empty() && processed_vertices.empty()) {
    if (current_clique.size() > 2) {
      std::vector<int> clique(current_clique.begin(), current_clique.end());
      std::sort(clique.begin(), clique.end());
      cliques.emplace_back(clique);
    }
    return;
  }

  // Select a pivot vertex from 'candidates' union 'processedVertices' with the
  // maximum degree
  std::set<int> union_set(candidates.begin(), candidates.end());
  union_set.insert(processed_vertices.begin(), processed_vertices.end());
  const int pivot =
      *std::max_element(union_set.begin(), union_set.end(),
                        [&graph](const int &s1, const int &s2) {
                          return graph[s1].size() < graph[s2].size();
                        });
  // std::cout << union_set.size() << " " << candidates.size() << " " <<
  // processed_vertices.size() << std::endl; std::cout << pivot << " pivot\n";

  // 'possibles' are vertices in 'candidates' that are not neighbours of the
  // 'pivot'
  std::set<int> possibles{};
  std::set_difference(candidates.begin(), candidates.end(),
                      graph[pivot].begin(), graph[pivot].end(),
                      std::inserter(possibles, possibles.begin()));

  // std::cout << possibles.size() << " possibles size\n";

  for (const int &vertex : possibles) {

    // Create a new clique including 'vertex'
    std::set<int> new_cliques(current_clique.begin(), current_clique.end());
    new_cliques.insert(vertex);

    // 'newCandidates' are the members of 'candidates' that are neighbours of
    // 'vertex'
    std::set<int> new_candidates{};
    std::set_intersection(
        candidates.begin(), candidates.end(), graph[vertex].begin(),
        graph[vertex].end(),
        std::inserter(new_candidates, new_candidates.begin()));

    // 'newProcessedVertices' are members of 'processedVertices' that are
    // neighbours of 'vertex'
    std::set<int> new_processed_vertices{};
    std::set_intersection(
        processed_vertices.begin(), processed_vertices.end(),
        graph[vertex].begin(), graph[vertex].end(),
        std::inserter(new_processed_vertices, new_processed_vertices.begin()));

    // Recursive call with the updated sets
    bron_kerbosch(new_cliques, new_candidates, new_processed_vertices, graph,
                  cliques);

    // Move 'vertex' from 'candidates' to 'processedVertices'
    candidates.erase(vertex);
    processed_vertices.insert(vertex);
  }
}

int main() {
  const int UPPER_BOUND = 10000;
  std::vector<int> primes{2};
  for (int i = 3; i < UPPER_BOUND; i += 2) {
    bool flag = true;
    for (auto p : primes) {
      if (i % p == 0) {
        flag = false;
        break;
      }
    }
    if (flag) {
      primes.push_back(i);
    }
  }

  std::cout << "Primes generated\n";

  std::vector<std::set<int>> neighbours(primes.size());
  for (int i = 0; i < primes.size(); i++) {
    for (int j = i + 1; j < primes.size(); j++) {
      auto strI = std::to_string(primes[i]);
      auto strJ = std::to_string(primes[j]);
      int pp1 = std::stoi(strI + strJ);
      int pp2 = std::stoi(strJ + strI);
      if (is_prime(pp1) && is_prime(pp2)) {
        neighbours[i].insert(j);
        neighbours[j].insert(i);
      }
    }
  }

  std::vector<std::vector<int>> cliques;
  std::set<int> current_clique, candidates, proccessed;
  for (int i = 0; i < primes.size(); i++) {
    candidates.insert(i);
  }
  bron_kerbosch(current_clique, candidates, proccessed, neighbours, cliques);
  std::cout << cliques.size() << " C size\n";
  std::sort(cliques.begin(), cliques.end(),
            [](std::vector<int> a, std::vector<int> b) {
              if (a.size() == b.size())
                return a[0] < b[0];
              return a.size() > b.size();
            });
  std::cout << cliques[0].size() << ": ";
  int sum = 0;
  for (auto i : cliques[0]) {
    sum += primes[i];
    std::cout << primes[i] << " ";
  }
  std::cout << std::endl;
  std::cout<< "Total: " << sum << "\n";

return 0;
}
