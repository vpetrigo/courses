#include "brackets.hpp"

#include <iostream>
#include <unordered_map>

using char_stack = Stack<char>;

static bool brackets_match(const char open_br, const char close_br) {
  static std::unordered_map<char, char> brackets_combinations{
      {']', '['}, {')', '('}, {'}', '{'}};

  return brackets_combinations[close_br] == open_br;
}

int main() {
  char_stack ch_stack;
  char ch{'\0'};
  std::size_t counter = 0;

  while (std::cin.get(ch) && !iscntrl(ch)) {
    ++counter;

    if (ch == '[' || ch == '{' || ch == '(') {
      // open brace - push it in our stack
      ch_stack.Push(ch);
    }
    else if (!brackets_match(ch_stack.Pop(), ch)) {
      // close brace did not match
      break;
    }
  }

  if (ch_stack.Empty()) {
    std::cout << "Success" << std::endl;
  }
  else {
    std::cout << counter << std::endl;
  }

  return 0;
}
