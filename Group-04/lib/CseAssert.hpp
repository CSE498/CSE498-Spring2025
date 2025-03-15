#pragma once

#include <concepts>
#include <iostream>
#include <optional>
#include <string>

// Entrypoints for assert macros.
//
// These use variadic macro to prevent accidentally splitting on commas within
// condition. Inspired by c++ proposal P2264R7.
//
// Curly braces are used (instead of parenthesis as in P2264R7) as these
// arguments are actually passed to the constructor of `AssertArgs`.
#define cse_assert(condition_msg...)                                  \
  internal_cse_assert_(internal_cse_assert_args_head_(condition_msg), \
                       {condition_msg})
#define cse_assert_never(...)                     \
  ::cse::_assert_internal::assert_never_noreturn( \
      __FILE__, __LINE__, __func__ __VA_OPT__(, __VA_ARGS__))
#define cse_assert_eq(args...)                                  \
  internal_cse_assert_eq_(internal_cse_assert_args_head_(args), \
                          internal_cse_assert_args_tail_(args), \
                          cse::_assert_internal::BinaryAssertArgs{args})
#define cse_assert_neq(args...)                                  \
  internal_cse_assert_neq_(internal_cse_assert_args_head_(args), \
                           internal_cse_assert_args_tail_(args), \
                           cse::_assert_internal::BinaryAssertArgs{args})

// These macros perform a best-effort recovery of the text of the original
// arguments for display output on assertion failure.
//
// This will incorrectly split arguments in the same way that std's assert macro
// does, but in this case only affects the display and not the logic. We could
// potentially implement a parser to determine more accurately how the arguments
// are split, but this is already an edge case.
#define internal_cse_assert_args_head_(head, tail...) #head
#define internal_cse_assert_args_tail_(head, tail...) #tail

// Internal macros which fill in the file, line number, etc. and call into the
// actual C++ functions.
#define internal_cse_assert_(condition_text, condition_msg...)        \
  ::cse::_assert_internal::assert_impl(condition_msg, condition_text, \
                                       __FILE__, __LINE__, __func__)
#define internal_cse_assert_eq_(lhs_text, rhs_text, rest...)                  \
  ::cse::_assert_internal::assert_eq_impl(rest, lhs_text, rhs_text, __FILE__, \
                                          __LINE__, __func__)
#define internal_cse_assert_neq_(lhs_text, rhs_text, rest...)                  \
  ::cse::_assert_internal::assert_neq_impl(rest, lhs_text, rhs_text, __FILE__, \
                                           __LINE__, __func__)

// Debug macros
#ifdef NDEBUG
// Adding (void)0 here ensures callers still
// needs to end the line with a semi-colon.
// Source: https://stackoverflow.com/a/1306618/4678913
#define dbg_assert(...) (void)0
#define dbg_assert_never(...) (void)0
#define dbg_assert_eq(...) (void)0
#define dbg_assert_neq(...) (void)0
#else
#define dbg_assert(...) cse_assert(__VA_ARGS__)
#define dbg_assert_never(...)                   \
  ::cse::_assert_internal::assert_never_return( \
      __FILE__, __LINE__, __func__ __VA_OPT__(, __VA_ARGS__))
#define dbg_assert_eq(...) cse_assert_eq(__VA_ARGS__)
#define dbg_assert_neq(...) cse_assert_neq(__VA_ARGS__)
#endif

// Do *not* access anything inside this namespace directly
namespace cse::_assert_internal {
#ifdef TEST_CSE_ASSERT
class AssertTestException : std::exception {};
void assert_fail() { throw AssertTestException(); }

// helper macros for catch2 tests
#ifdef CATCH_VERSION_MAJOR
#define REQUIRE_ASSERT(...) \
  REQUIRE_THROWS_AS(__VA_ARGS__, cse::_assert_internal::AssertTestException)
#define REQUIRE_NOASSERT(...) REQUIRE_NOTHROW(__VA_ARGS__)
#endif

#else
[[noreturn]] void assert_fail() { std::abort(); }
#endif

// This class allows us to accept both a condition and an optional message.
//
// The message can't be a macro argument, since if it's the first argument then
// it would have to be mandatory. It can't be the last argument since there's no
// way to extract just the last argument, and even if we could we wouldn't know
// if it's part of the condition or if it's the message.
//
// Using a class provides a constructor which does the argument splitting at the
// language level, rather than the pre-processor level.
class AssertArgs {
 public:
  bool condition;
  std::optional<std::string> message = std::nullopt;
  AssertArgs(bool condition) : condition(condition) {};
  AssertArgs(bool condition, std::string message)
      : condition(condition), message(message) {};
};

template <typename T>
class BinaryAssertArgs {
 public:
  T lhs;
  T rhs;
  std::optional<std::string> message = std::nullopt;

  BinaryAssertArgs(T lhs, T rhs) : lhs(lhs), rhs(rhs) {};
  BinaryAssertArgs(T lhs, T rhs, std::string message)
      : lhs(lhs), rhs(rhs), message(message) {};
};

void print_assert_message(
    std::optional<std::string> message_opt = std::nullopt) {
  std::cerr << "Assertion ";
  std::cerr << "failed";
  if (auto message = message_opt) {
    std::cerr << ": " << message.value();
  } else {
    std::cerr << "!";
  }
}

void print_location(const char *file, int line, const char *function) {
  std::cerr << "\nLocated at: " << file << ":" << line << " (in function "
            << function << ")\n";
}

void assert_impl(AssertArgs const &args, const char *args_text,
                 const char *file, int line, const char *function) {
  if (args.condition) {
    return;
  }
  std::string cond_string = std::string{args_text};

  print_assert_message(args.message);
  std::cerr << "\n  Condition evaluated to "
               "false: "
            << cond_string << "\n";
  print_location(file, line, function);
  assert_fail();
}

template <typename T>
concept printable = requires(T output) { std::cerr << output; };

template <typename T>
  requires std::equality_comparable<T>
void assert_eq_impl(BinaryAssertArgs<T> const &args, const char *lhs_text,
                    const char *rhs_text, const char *file, int line,
                    const char *function) {
  if (args.lhs == args.rhs) {
    return;
  }
  std::string lhs_string = std::string{lhs_text};
  std::string rhs_string = std::string{rhs_text};

  print_assert_message(args.message);
  if constexpr (printable<T>) {
    std::cerr << " These values are different:\n"
              << "   left: " << args.lhs << "\n  right: " << args.rhs << "\n";
    print_location(file, line, function);
  } else {
    std::cerr << "  These expressions evaluated to different values:\n"
              << "   left: " << lhs_string << "\n  right: " << rhs_string
              << "\n";
    print_location(file, line, function);
    std::cerr << "hint: implement operator<< to see the underlying values\n";
  }

  assert_fail();
}

template <typename T>
  requires std::equality_comparable<T>
void assert_neq_impl(BinaryAssertArgs<T> const &args, const char *lhs_text,
                     const char *rhs_text, const char *file, int line,
                     const char *function) {
  if (args.lhs != args.rhs) {
    return;
  }
  std::string lhs_string = std::string{lhs_text};
  std::string rhs_string = std::string{rhs_text};

  print_assert_message(args.message);
  if constexpr (printable<T>) {
    std::cerr << " These values are the same:\n"
              << "   left: " << args.lhs << "\n  right: " << args.rhs << "\n";
    print_location(file, line, function);
  } else {
    std::cerr << "  These expressions evaluated to the same value:\n"
              << "   left: " << lhs_string << "\n  right: " << rhs_string
              << "\n";
    print_location(file, line, function);
    std::cerr << "hint: implement operator<< to see the underlying values\n";
  }

  assert_fail();
}

// technically does return when in test mode
#ifndef TEST_CSE_ASSERT
[[noreturn]]
#endif
void assert_never_noreturn(
    const char *file, int line, const char *function,
    std::optional<std::string> message_opt = std::nullopt) {
  print_assert_message(message_opt);
  print_location(file, line, function);
  assert_fail();
}

// dbg_assert_never doesn't uphold noreturn in release mode (since it is a
// no-op), so this function acts like AssertNeverNoReturn but without the
// [[noreturn]] marker
void assert_never_return(
    const char *file, int line, const char *function,
    std::optional<std::string> message_opt = std::nullopt) {
  assert_never_noreturn(file, line, function, message_opt);
}

}  // namespace cse::_assert_internal
