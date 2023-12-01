#include <iostream>
#include <unordered_map>

#include "aoc.h"

using aoc::read_input;

std::pair<bool, int> starts_digit(int ind, const std::string& line) {
  std::unordered_map<std::string, int> nums{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  for (int len : {3, 4, 5}) {
    auto substring = line.substr(ind, (ind + len) <= line.size() ? len : 0);
    if (nums.find(substring) != nums.end()) {
      return {true, nums[substring]};
    }
  }
  return {false, 0};
}

std::string find_digit(const std::string& line, int delta, bool part_two) {
  for (int ind = delta > 0 ? 0 : line.size() - 1; ind < line.size();
       ind += delta) {
    char c = line[ind];
    if (isdigit(c)) {
      std::string s(1, c);
      return s;
    }
    if (part_two) {
      auto digit_pair = starts_digit(ind, line);
      if (digit_pair.first) {
        return std::to_string(digit_pair.second);
      }
    }
  }
  return "";
}

long solve(bool part_two) {
  auto lines = read_input(1);
  long total = 0;

  for (auto& line : lines) {
    total += std::stoi(find_digit(line, 1, part_two) +
                       find_digit(line, -1, part_two));
  }

  return total;
}

int main() {
  long part_one = solve(false);
  long part_two = solve(true);

  std::cout << "Part one: " << part_one << ". Part two: " << part_two << '\n';

  return 0;
}