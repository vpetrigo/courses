#include <iostream>
#include <algorithm>

int can_be_palindrome(const std::string &s);

int main() 
{
  std::string palindrome_candidate;

  std::cin >> palindrome_candidate;
  std::cout << can_be_palindrome(palindrome_candidate) << std::endl;

  return 0;
}

int can_be_palindrome(const std::string &s) 
{
  auto mid = std::next(std::cbegin(s), s.size() / 2);
  auto diff_it = std::mismatch(std::cbegin(s), mid, std::crbegin(s)).first;
  auto diff_index = std::distance(std::cbegin(s), diff_it);

  if (std::equal(std::cbegin(s), diff_it, std::crbegin(s)) &&
      std::equal(std::next(diff_it), mid, std::next(std::crbegin(s), diff_index))) {
    return diff_index;
  }
  else {
    return s.size() - diff_index - 1;
  }
}

