#include <iostream>
#include <unordered_map>

#include "absl/strings/str_split.h"
#include "aoc.h"

using aoc::read_input;

bool is_valid(const std::string& set,
              const std::unordered_map<std::string, int>& counts) {
  std::vector<std::string> cubes = absl::StrSplit(set, ", ");
  for (auto& cube : cubes) {
    std::vector<std::string> count_split = absl::StrSplit(cube, " ");
    int num_cubes = std::stoi(count_split[0]);
    if (counts.at(count_split[1]) < num_cubes) {
      return false;
    }
  }
  return true;
}

long cube_factor(const std::vector<std::string>& sets) {
  std::unordered_map<std::string, int> counts = {
      {"red", 0}, {"green", 0}, {"blue", 0}};
  for (auto& set : sets) {
    std::vector<std::string> cubes = absl::StrSplit(set, ", ");
    for (auto& cube : cubes) {
      std::vector<std::string> count_split = absl::StrSplit(cube, " ");
      int num_cubes = std::stoi(count_split[0]);
      auto elem = counts.find(count_split[1]);
      elem->second = std::max(elem->second, num_cubes);
    }
  }
  return counts.at("red") * counts.at("green") * counts.at("blue");
}

long solve(bool part_two) {
  auto input = read_input(2);

  const std::unordered_map<std::string, int> counts = {
      {"red", 12}, {"green", 13}, {"blue", 14}};
  long total = 0;

  for (const auto& line : input) {
    std::vector<std::string> game_split = absl::StrSplit(line, ": ");
    int id = std::stoi(game_split[0].substr(5, game_split[0].size() - 5));
    std::vector<std::string> sets = absl::StrSplit(game_split[1], "; ");
    if (part_two) {
      total += cube_factor(sets);
    } else {
      bool all_valid = std::all_of(
          sets.begin(), sets.end(),
          [counts](std::string& set) { return is_valid(set, counts); });
      if (all_valid) {
        total += id;
      }
    }
  }
  return total;
}

int main() {
  std::cout << "Part one: " << solve(false) << ". Part two: " << solve(true)
            << '\n';
  return 0;
}