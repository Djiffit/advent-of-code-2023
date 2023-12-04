#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "absl/strings/str_split.h"
#include "aoc.h"

using aoc::read_input;

std::unordered_set<int> read_numbers(const std::string& number_list) {
  std::vector<std::string> nums =
      absl::StrSplit(number_list, ' ', absl::SkipEmpty());
  std::unordered_set<int> ints;
  std::transform(nums.begin(), nums.end(), std::inserter(ints, ints.begin()),
                 [](const std::string& str) { return std::stoi(str); });
  return ints;
}

std::pair<std::unordered_set<int>, std::unordered_set<int>> read_line(
    int number, const std::vector<std::string>& lines) {
  std::vector<std::string> card_split = absl::StrSplit(lines[number], ": ");
  std::vector<std::string> number_split = absl::StrSplit(card_split[1], " | ");

  auto my_nums = read_numbers(number_split[0]);
  auto winning_nums = read_numbers(number_split[1]);

  return {my_nums, winning_nums};
}

long count_winnings(int number, std::vector<std::string>& lines,
                    std::map<int, long>& totals) {
  auto [my_nums, winning_nums] = read_line(number, lines);
  totals[number] += 1;

  long total = 0;
  long score = 0;
  for (auto num : my_nums) {
    if (winning_nums.find(num) != winning_nums.end()) {
      total += 1;
      score = score == 0 ? 1 : score * 2;
    }
  }

  for (int new_match = 1; new_match <= total; new_match += 1) {
    if (new_match + number >= lines.size()) break;
    totals[new_match + number] += totals[number];
  }

  return score;
}

long solve(bool part_two) {
  auto input = read_input(4);
  std::map<int, long> totals;
  long total = 0;

  for (int i = 0; i < input.size(); i++) {
    int wins = count_winnings(i, input, totals);
    total += part_two ? totals[i] : wins;
  }

  return total;
}

int main() {
  long part_one = solve(false);
  long part_two = solve(true);

  std::cout << "Part one: " << part_one << ". Part two: " << part_two << '\n';

  return 0;
}