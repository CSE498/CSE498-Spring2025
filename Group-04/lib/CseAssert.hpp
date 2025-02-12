#pragma once

#include <iostream>
#include <optional>
#include <string>

// Uses variadic macro to prevent accidentally splitting on commas within
// condition. Inspired by c++ proposal P2264R7.
//
// Curly braces are used instead of parenthesis as this is actually a
// constructor for `AssertArgs`.
#define cse_assert(condition_msg...) _cse_assert_internal({condition_msg})
#define _cse_assert_internal(condition_msg...)                             \
  ::cse::_assert_internal::Assert(condition_msg, #condition_msg, __FILE__, \
                                  __LINE__, __func__)

#define cse_assert_never(...)                              \
  ::cse::_assert_internal::AssertNever(__FILE__, __LINE__, \
                                       __func__ __VA_OPT__(, __VA_ARGS__))

#ifdef NDEBUG
// Adding (void)0 here ensures callers still needs to end the line with a
// semi-colon. Source: https://stackoverflow.com/a/1306618/4678913
#define dbg_assert(...) (void)0
#else
#define dbg_assert(...) cse_assert(__VA_ARGS__)
#endif

// Do *not* access anything inside this namespace directly
namespace cse::_assert_internal {
// underscore followed by capital letter is reserved
#ifdef _cse_ASSERT_TEST
class AssertTestException : std::exception {};
void Fail() { throw AssertTestException(); }
#else
[[noreturn]] void Fail() { std::abort(); }
#endif

// This class allows us to accept both a condition and an optional message. The
// message can't be a macro argument, since if it's the first argument then it
// would have to be mandatory. It can't be the last argument since there's no
// way to extract just the last argument, and even if we could we wouldn't know
// if it's part of the condition or if it's the message.
//
// Using a class provides a constructor which does the argument splitting at
// the language level, rather than the pre-processor level.
class AssertArgs {
 public:
  bool condition;
  std::optional<const char *> message = std::nullopt;

  AssertArgs(bool condition) : condition(condition) {};
  AssertArgs(bool condition, const char *message)
      : condition(condition), message(message) {};
};

void Assert(AssertArgs const &args, const char *args_text, const char *file,
            int line, const char *function) {
  if (!args.condition) {
    // TODO: extract just the condition
    std::string cond_string = std::string{args_text};
    cond_string = cond_string.substr(1, cond_string.size() - 2);

    std::cout << "Assertion failed!";
    if (auto message = args.message) {
      std::cout << " " << message.value();
    }
    std::cout << "\n";

    std::cout << "  Condition evaluated to false: " << cond_string << "\n";
    std::cout << "  Located at: " << file << ":" << line << " (in function "
              << function << ")\n";
    Fail();
  }
}

// this technically does return when using the testing mode
#ifndef _cse_ASSERT_TEST
[[noreturn]]
#endif
void AssertNever(const char *file, int line, const char *function,
                 std::optional<const char *> message_opt = std::nullopt) {

  std::cout << "Assertion failed!";
  if (auto message = message_opt) {
    std::cout << " " << message.value();
  }
  std::cout << "\n";
  std::cout << "  Located at: " << file << ":" << line << " (in function "
            << function << ")\n";
  Fail();
}

}  // namespace cse::_assert_internal
