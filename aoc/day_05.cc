#include <iostream>
#include <unordered_map>

#include "absl/strings/str_split.h"
#include "aoc.h"

using aoc::read_input;

long resolve_next_value(
    const std::vector<std::pair<long, std::pair<long, long>>>& mapping,
    long number) {
  for (const auto& element : mapping) {
    if (number >= element.first &&
        number < element.second.second + element.first) {
      return element.second.first + number - element.first;
    }
  }
  return number;
}

std::vector<std::pair<long, long>> resolve_next_range(
    const std::vector<std::pair<long, std::pair<long, long>>>& mapping,
    std::pair<long, long> range) {
  std::vector<std::pair<long, long>> new_ranges;
  if (mapping[0].first > range.first + range.second) {
    return {range};
  }
  for (const auto& element : mapping) {
    if (range.second == 0) return new_ranges;
    long elem_end = element.first + element.second.second;
    long range_end = range.first + range.second;

    // Is in the middle.
    if (range.first < element.first && elem_end < range_end) {
      if (range.first != element.first)
        new_ranges.push_back({range.first, element.first - range.first});
      new_ranges.push_back({element.second.first, element.second.second});
      range = {elem_end, range_end - element.first - element.second.second};
      // Starts in middle and ends after
    } else if (range.first < element.first && elem_end >= range_end &&
               element.first < range_end) {
      new_ranges.push_back({element.second.first, range_end - element.first});
      new_ranges.push_back({range.first, element.first - range.first});
      return new_ranges;
      // Starts before and ends in middle of range
    } else if (range.first > element.first && elem_end > range.first &&
               elem_end < range_end) {
      new_ranges.push_back({element.second.first + range.first - element.first,
                            elem_end - range.first});
      range = {elem_end, range_end - element.first - element.second.second};
      // Encompasses completely
    } else if (element.first <= range.first && elem_end >= range_end) {
      new_ranges.push_back(
          {element.second.first + range.first - element.first, range.second});
      return new_ranges;
    }
  }

  if (range.second > 0) new_ranges.push_back({range});
  return new_ranges;
}

long solve(bool part_two) {
  auto lines = read_input(5);

  std::vector<long> seeds;
  std::vector<std::string> seed_string = absl::StrSplit(lines[0], ": ");
  std::vector<std::string> seeds_string =
      absl::StrSplit(seed_string[1], " ", absl::SkipEmpty());
  std::transform(seeds_string.begin(), seeds_string.end(),
                 std::back_inserter(seeds),
                 [](const std::string seed) { return std::stol(seed); });

  std::map<std::string, std::vector<std::pair<long, std::pair<long, long>>>>
      mappings;
  std::vector<std::string> keys;

  for (long index = 2; index < lines.size(); index++) {
    if (!std::isdigit(lines[index].at(0))) {
      std::string key = lines[index].substr(0, lines[index].size() - 5);
      keys.push_back(key);
      index += 1;
      std::vector<std::pair<long, std::pair<long, long>>> ranges;
      while (lines[index].size() > 0 && std::isdigit(lines[index].at(0))) {
        std::vector<long> long_numbers;
        std::vector<std::string> string_numbers =
            absl::StrSplit(lines[index], " ", absl::SkipEmpty());
        std::transform(
            string_numbers.begin(), string_numbers.end(),
            std::back_inserter(long_numbers),
            [](const std::string number) { return std::stol(number); });
        ranges.push_back({long_numbers[1], {long_numbers[0], long_numbers[2]}});
        index += 1;
      }

      std::sort(ranges.begin(), ranges.end());
      mappings.insert({key, std::move(ranges)});
    }
  }

  long lowest = LONG_MAX;
  if (!part_two) {
    std::vector<long> new_seeds;
    for (auto& key : keys) {
      std::transform(seeds.begin(), seeds.end(), std::back_inserter(new_seeds),
                     [&key, &mappings](long number) {
                       return resolve_next_value(mappings[key], number);
                     });
      seeds = new_seeds;
      new_seeds.clear();
    }

    for (auto seed : seeds) {
      lowest = std::min(lowest, seed);
    }
  } else {
    std::vector<std::pair<long, long>> ranges;
    std::vector<std::pair<long, long>> new_ranges;
    for (int i = 0; i < seeds.size(); i += 2) {
      ranges.push_back({seeds[i], seeds[i + 1]});
    }
    for (auto& key : keys) {
      for (auto& range : ranges) {
        auto new_additions = resolve_next_range(mappings[key], range);
        new_ranges.insert(new_ranges.end(), new_additions.begin(),
                          new_additions.end());
      }
      ranges = new_ranges;
      new_ranges.clear();
    }

    for (auto& range : ranges) {
      lowest = std::min(range.first, lowest);
    }
  }
  return lowest;
}

int main() {
  long part_one = solve(false);
  long part_two = solve(true);

  std::cout << "Part one: " << part_one << ". Part two: " << part_two << '\n';

  return 0;
}