#include "brackets.hpp"

#include <iostream>
#include <set>
#include <unordered_map>

using CharStack = Stack<char>;
using SizeStack = Stack<std::size_t>;

static bool brackets_match(const char open_br, const char close_br)
{
  static std::unordered_map<char, char> brackets_combinations{
      {']', '['}, {')', '('}, {'}', '{'}};

  return brackets_combinations[close_br] == open_br;
}

static bool intermediate_symbol(const char ch)
{
  static std::set<char> punct{';', ',', '.', ':', '!', '?'};

  return (isalnum(ch) != 0) || (punct.find(ch) != punct.cend());
}

int main()
{
  CharStack ch_stack;
  SizeStack size_stack;
  char ch{'\0'};

  for (std::size_t counter = 1; std::cin.get(ch) && !iscntrl(ch); ++counter) {
    if (ch == '[' || ch == '{' || ch == '(') {
      // open brace - push it in our stack
      ch_stack.Push(ch);
      size_stack.Push(counter);
    }
    else if (!intermediate_symbol(ch)) {
      if (ch_stack.Empty() || !brackets_match(ch_stack.Pop(), ch)) {
        // close brace did not match
        size_stack.Push(counter);

        break;
      }
      else {
        // pop the last index of open brace
        size_stack.Pop();
      }
    }
  }

  if (size_stack.Empty() && ch_stack.Empty()) {
    std::cout << "Success" << std::endl;
  }
  else {
    std::cout << size_stack.Pop() << std::endl;
  }

  return 0;
}
