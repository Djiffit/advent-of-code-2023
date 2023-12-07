#include <iostream>
#include <unordered_map>

#include "absl/strings/str_split.h"
#include "aoc.h"

using aoc::read_input;

enum HandType {
  HIGH_CARD = 1,
  ONE_PAIR = 2,
  TWO_PAIR = 3,
  THREE_OF_A_KIND = 4,
  FULL_HOUSE = 5,
  FOUR_OF_A_KIND = 6,
  FIVE_OF_A_KIND = 7,
};

class Hand {
 private:
  bool part_two;
  void set_hand_value(std::string& cards) { hand_type = get_hand_value(cards); }
  std::vector<std::string> all_cards = {"2", "3", "4", "5", "6", "7",
                                        "8", "9", "T", "Q", "K", "A"};

  void find_best_hand_value(std::string cards) {
    std::vector<int> joker_indices;
    for (int index = 0; index < cards.size(); index++) {
      if (cards[index] == 'J') joker_indices.push_back(index);
    }
    if (joker_indices.size() > 0)
      hand_type = fill_jokers(0, cards, joker_indices);
    else
      hand_type = get_hand_value(cards);
  }

  HandType fill_jokers(int index, std::string& cards,
                       std::vector<int>& joker_positions) {
    if (index == joker_positions.size()) {
      return get_hand_value(cards);
    }
    auto best_hand = HIGH_CARD;
    int current_ind = joker_positions[index];
    for (auto card : all_cards) {
      cards.replace(cards.begin() + current_ind,
                    cards.begin() + current_ind + 1, card);
      best_hand =
          std::max(best_hand, fill_jokers(index + 1, cards, joker_positions));
    }
    return best_hand;
  }

  HandType get_hand_value(std::string& cards) {
    std::unordered_map<char, int> counts;
    for (auto& card : cards) {
      counts[card] += 1;
    }

    std::vector<int> count_vec;
    for (auto& pair : counts) {
      count_vec.push_back(pair.second);
    }

    auto max_element = std::max_element(count_vec.begin(), count_vec.end());
    if (count_vec.size() == 1)
      return FIVE_OF_A_KIND;
    else if (count_vec.size() == 2 && (count_vec[0] == 1 || count_vec[0] == 4))
      return FOUR_OF_A_KIND;
    else if (count_vec.size() == 2 && (count_vec[0] == 2 || count_vec[0] == 3))
      return FULL_HOUSE;
    else if (*max_element == 3)
      return THREE_OF_A_KIND;
    else if (*max_element == 2 && count_vec.size() == 3)
      return TWO_PAIR;
    else if (*max_element == 2 && count_vec.size() == 4)
      return ONE_PAIR;
    else
      return HIGH_CARD;
  }

 public:
  HandType hand_type;
  std::string cards;
  long bid;

  Hand(std::string cards, long bid, bool part_two)
      : part_two(part_two), cards(cards), bid(bid) {
    set_hand_value(cards);
    find_best_hand_value(cards);
  }

  static bool compare_hands(const Hand* left, const Hand* right) {
    std::map<char, int> elem_to_value = {
        {'2', 2},  {'3', 3},
        {'4', 4},  {'5', 5},
        {'6', 6},  {'7', 7},
        {'8', 8},  {'9', 9},
        {'T', 10}, {'J', left->part_two ? 1 : 11},
        {'Q', 12}, {'K', 13},
        {'A', 14}};
    if (left->hand_type != right->hand_type)
      return left->hand_type < right->hand_type;
    for (int index = 0; index < left->cards.size(); index++) {
      if (left->cards.at(index) != right->cards.at(index))
        return elem_to_value[left->cards.at(index)] <
               elem_to_value[right->cards.at(index)];
    }
    return false;
  }
};

long solve(bool part_two) {
  auto lines = read_input(7);
  long long total = 0;
  std::vector<Hand*> hands;

  for (auto& line : lines) {
    std::vector<std::string> hand_bid = absl::StrSplit(line, " ");
    hands.push_back(new Hand(hand_bid[0], std::stol(hand_bid[1]), part_two));
  }

  std::sort(hands.begin(), hands.end(), Hand::compare_hands);

  for (int index = 0; index < hands.size(); index++) {
    auto hand = hands[index];
    total += (index + 1) * hand->bid;
  }

  return total;
}

int main() {
  long part_one = solve(false);
  long part_two = solve(true);

  std::cout << "Part one: " << part_one << ". Part two: " << part_two << '\n';

  return 0;
}