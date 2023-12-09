#include <iostream>
#include <numeric>
#include <ranges>
#include <unordered_map>

#include "absl/strings/str_split.h"
#include "aoc.h"

using aoc::read_input;
using aoc::LeftRight;

long long find_loop_size(const std::string& cmds, const auto& routes, std::string curr) {
  int steps = 0, prev = 0;
  while (true) {
    if (curr[curr.size() - 1] == 'Z') {
      if (prev != 0) {
        return steps - prev;
      }
      prev = steps - prev;
    }
    curr = cmds[steps % cmds.size()] == 'L' ? routes.at(curr).left : routes.at(curr).right;
    steps += 1;
  }
}

long long solve(bool part_two) {
  auto lines = read_input(8);

  std::map<std::string, LeftRight> routes;
  auto route_vals =
      std::views::drop(lines, 2)
      | std::views::transform([](const std::string& line) { return std::make_pair(line.substr(0, 3), LeftRight{line.substr(7, 3), line.substr(12, 3)}); });
  routes.insert(route_vals.begin(), route_vals.end());
  auto lengths = routes
      | std::views::transform([part_two](const auto& pair) { return pair.first; }) 
      | std::views::filter([part_two](const auto& elem) { return part_two ? elem.at(elem.size() - 1) == 'A' : elem == "AAA"; })
      | std::views::transform([&lines, &routes](const std::string& pos) { return find_loop_size(lines[0], routes, pos); });
  return std::reduce(lengths.begin(), lengths.end(), *lengths.begin(), [](auto acc, auto val) { return std::lcm(acc, val); });
}

int main() {
  std::cout << "Part one: " << solve(false) << ". Part two: " << solve(true) << '\n';
  return 0;
}
