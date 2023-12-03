#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "aoc.h"

using aoc::read_input;

template <>
struct std::hash<std::pair<int, int>> {
  size_t operator()(const std::pair<int, int>& p) const noexcept {
    return p.first ^ p.second;
  }
};

bool has_adjacent(std::vector<std::string>& data, int y, int x, bool part_two,
                  std::unordered_set<std::pair<int, int>>& stars) {
  for (int y_diff : {-1, 0, 1}) {
    for (int x_diff : {-1, 0, 1}) {
      int new_y = y + y_diff;
      int new_x = x + x_diff;

      if ((x_diff == 0 && y_diff == 0) || new_y < 0 || new_y >= data.size() ||
          new_x < 0 || new_x >= data[0].size())
        continue;

      if (part_two) {
        if (data[new_y].at(new_x) == '*') {
          stars.insert({new_y, new_x});
        }
      } else if (!isdigit(data[new_y].at(new_x)) &&
                 data[new_y].at(new_x) != '.') {
        return true;
      }
    }
  }
  return false;
}

int read_number(std::vector<std::string>& data, int y, int start_x, int end_x) {
  int total = 0;
  for (int x = start_x; x <= end_x; x++) {
    total *= 10;
    total += (data[y].at(x) - '0');
  }
  return total;
}

long solve(bool part_two) {
  auto input = read_input(3);

  std::vector<std::pair<int, int>> start_pos;
  std::vector<std::pair<int, int>> end_pos;
  std::vector<std::pair<int, int>> stars;

  std::unordered_map<std::pair<int, int>, std::unordered_set<int>,
                     std::hash<std::pair<int, int>>>
      star_neighbors;

  long total = 0;

  for (int y = 0; y < input.size(); y++) {
    for (int x = 0; x < input[y].size(); x++) {
      char elem = input[y].at(x);
      if (isdigit(elem) && (x == 0 || !isdigit(input[y].at(x - 1)))) {
        start_pos.push_back({y, x});
      }
      if (isdigit(elem) &&
          (x == input[y].size() - 1 || !isdigit(input[y].at(x + 1)))) {
        end_pos.push_back({y, x});
      }
      if (elem == '*') {
        stars.push_back({y, x});
      }
    }
  }

  for (int ind = 0; ind < start_pos.size(); ind++) {
    auto [y, start_x] = start_pos[ind];
    auto [start_y, end_x] = end_pos[ind];

    std::unordered_set<std::pair<int, int>, std::hash<std::pair<int, int>>>
        stars;
    for (auto x = start_x; x <= end_x; x++) {
      if (part_two) {
        has_adjacent(input, start_y, x, part_two, stars);
      }
      if (!part_two && has_adjacent(input, start_y, x, part_two, stars)) {
        total += read_number(input, start_y, start_x, end_x);
        break;
      }
    }
    if (part_two) {
      for (auto& star : stars) {
        auto star_elem = star_neighbors.find(star);
        int number = read_number(input, start_y, start_x, end_x);
        if (star_elem == star_neighbors.end()) {
          std::unordered_set<int> nums{number};
          star_neighbors.insert({star, nums});
        } else {
          if (star_elem->second.find(number) != star_elem->second.end()) {
            total += number * number;  // Hack for duplicate numbers on a gear.
          }
          star_elem->second.insert(number);
        }
      }
    }
  }

  for (const auto& [star, neighbors] : star_neighbors) {
    if (neighbors.size() == 2) {
      long num = 1;
      for (auto neighbor = neighbors.begin(); neighbor != neighbors.end();
           neighbor++) {
        num = num * (*neighbor);
      }
      total += num;
    }
  }
  return total;
}

int main() {
  std::cout << "Part one: " << solve(false) << ". Part two: " << solve(true)
            << '\n';
  return 0;
}