#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace aoc {

std::vector<std::string> read_input(int day) {
  std::string file_name = "/tmp/output" + std::to_string(day) + ".txt";
  if (access(file_name.c_str(), F_OK) != 0) {
    std::ifstream input_file("aoc/.env");
    std::string cookie;
    std::getline(input_file, cookie);
    std::string request = "curl https://adventofcode.com/2023/day/" +
                          std::to_string(day) +
                          "/input "
                          "-H 'Cookie: " +
                          cookie + "' > " + file_name;
    system(request.c_str());
  }
  std::vector<std::string> lines;
  std::ifstream input_file(file_name);

  std::string line;
  while (std::getline(input_file, line)) {
    lines.push_back(std::move(line));
  }
  input_file.close();

  return lines;
}

std::vector<long> read_input_nums(int day) {
  auto inputs_string = read_input(day);
  std::vector<long> nums;
  for (auto& val : inputs_string) {
    nums.push_back(std::stol(val));
  }
  return nums;
}

struct LeftRight {
  std::string left;
  std::string right;
};

struct Coord {
  long long y;
  long long x;
};

}  // namespace aoc