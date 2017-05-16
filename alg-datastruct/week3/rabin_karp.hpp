#ifndef _RABIN_KARP_HPP_
#define _RABIN_KARP_HPP_

#include <iterator>
#include <string>
#include <vector>

template <typename T>
T pow_fast_modulo(T base, T exp, T modulo)
{
  std::size_t result = 1;

  while (exp > 0) {
    if (exp % 2 == 1) {
      result = result * base % modulo;
    }

    exp >>= 1;
    base = (base * base) % modulo;
  }

  return result;
}

template <typename StrIt>
std::size_t StrPolynomialHash(StrIt first, StrIt last, std::size_t coeff,
                              std::size_t modulo)
{
  std::size_t hash_val{0};
  auto max_power = static_cast<std::size_t>(std::distance(first, last));

  while (first != last) {
    hash_val = (hash_val +
                static_cast<std::size_t>(*first++) *
                    pow_fast_modulo(coeff, --max_power, modulo) % modulo) %
               modulo;
  }

  return hash_val;
}

class RabinKarp {
 public:
  static constexpr std::size_t coeff = 263;
  static constexpr std::size_t prime = 1000000007;

  explicit RabinKarp(const std::string& pattern)
      : pattern_{pattern},
        pattern_hash_{StrPolynomialHash(std::rbegin(pattern_),
                                        std::rend(pattern_), coeff, prime)},
        pattern_length_{pattern_.size()},
        x_p_{pow_fast_modulo(coeff, pattern_length_ - 1, prime)}
  {
  }

  std::vector<std::size_t> GetPatternOccurence(const std::string& text)
  {
    std::vector<std::size_t> window_hash(text.size() - pattern_length_ + 1);
    std::size_t new_hash{0};
    auto window_hash_it = window_hash.begin();
    auto window_begin = std::crbegin(text);
    auto window_end = std::next(window_begin, pattern_length_);
    const auto text_end = std::crend(text);
    *window_hash_it++ =
        StrPolynomialHash(window_begin++, window_end++, coeff, prime);

    while (window_end != text_end + 1) {
      // add prime to the previous hash to prevent negative value during
      // substraction
      new_hash =
          (*std::prev(window_hash_it) + prime -
           x_p_ * static_cast<std::size_t>(*std::prev(window_begin)) % prime) %
          prime;
      new_hash = (new_hash * coeff % prime + *std::prev(window_end)) % prime;
      *window_hash_it++ = new_hash;
      ++window_begin;
      ++window_end;
    }

    std::vector<std::size_t> pattern_occur;

    for (std::size_t i = window_hash.size() - 1; i < window_hash.size(); --i) {
      if (window_hash[i] == pattern_hash_ &&
          std::equal(pattern_.crbegin(), pattern_.crend(),
                     text.crbegin() + i)) {
        pattern_occur.push_back(text.size() - pattern_length_ - i);
      }
    }

    return pattern_occur;
  }

  const std::size_t GetPatternHash() const { return pattern_hash_; }
 private:
  std::string pattern_;
  std::size_t pattern_hash_;
  std::size_t pattern_length_;
  std::size_t x_p_;
};

#endif  // _RABIN_KARP_HPP_
