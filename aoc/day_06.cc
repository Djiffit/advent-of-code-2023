#include <cmath>
#include <iostream>
#include <unordered_map>

#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "aoc.h"

using aoc::read_input;

bool will_win(int hold_down_time, int total_time, int distance) {
  int run_time = total_time - hold_down_time;
  return run_time * hold_down_time > distance;
}

long long find_win_change(long long total_time, long long distance) {
  long long first_root =
      ((-total_time) + sqrt(total_time * total_time - (-4) * (-distance))) /
      (-2);
  long long second_root =
      ((-total_time) - sqrt(total_time * total_time - (-4) * (-distance))) /
      (-2);
  return std::max(first_root, second_root) - std::min(first_root, second_root);
}

long solve(bool part_two) {
  auto lines = read_input(6);

  std::vector<std::string> times =
      absl::StrSplit(lines[0], " ", absl::SkipEmpty());
  std::vector<std::string> distances =
      absl::StrSplit(lines[1], " ", absl::SkipEmpty());

  if (part_two) {
    times.erase(times.begin());
    distances.erase(distances.begin());
    return find_win_change(atoll(absl::StrJoin(times, "").c_str()),
                           atoll(absl::StrJoin(distances, "").c_str()));
  }

  int winners = 1;
  for (int index = 1; index < times.size(); index++) {
    int total_wins = 0;
    int time = std::stoi(times[index]);
    int distance = std::stoi(distances[index]);
    for (int hold_down = 1; hold_down <= time; hold_down++) {
      total_wins += will_win(hold_down, time, distance) ? 1 : 0;
    }
    if (total_wins > 0) winners = winners * total_wins;
  }
  return winners;
}

int main() {
  long part_one = solve(false);
  long part_two = solve(true);

  std::cout << "Part one: " << part_one << ". Part two: " << part_two << '\n';

  return 0;
}