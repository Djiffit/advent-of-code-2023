#include "aoc.h"

using aoc::read_input;

std::vector<long> read_line(const std::string& line) {
  std::vector<std::string> nums = absl::StrSplit(line, " ");
  return std::reduce(nums.begin(), nums.end(), std::vector<long>{}, [](std::vector<long>& values, std::string& val) { values.push_back(std::stol(val)); return values; });
}

long next_value(const std::string& line, bool part_two) {
  std::vector<long> curr_vals = read_line(line);
  std::vector<std::vector<long>> rows = {curr_vals};
  while (!std::ranges::all_of(rows[rows.size() - 1], [](auto val) { return val == 0; })) {
    std::vector<long> new_vals;
    for (int i = 0; i < curr_vals.size() - 1; i++) {
      new_vals.push_back(curr_vals[i + 1] - curr_vals[i]);
    }
    rows.push_back(new_vals);
    curr_vals = new_vals;
  }
  for (int index = rows.size() - 2; index >= 0; index--) {
    auto& row = rows.at(index);
    auto& prev_row = rows.at(index + 1);
    row.insert(row.begin(), row.at(0) - prev_row.at(0));
    row.push_back(row.at(row.size() - 1) + prev_row.at(prev_row.size() - 1));
  }
  return part_two ? rows[0].at(0) : rows[0].at(rows[0].size() - 1);
}

long solve(bool part_two) {
  auto values = read_input(9) | std::views::transform([part_two](const auto& line) { return next_value(line, part_two); });
  return std::reduce(values.begin(), values.end(), 0, [](long acc, long val) { return acc + val; });
}

int main() {
  std::cout << "Part one: " << solve(false) << ". Part two: " << solve(true) << '\n';
  return 0;
}
