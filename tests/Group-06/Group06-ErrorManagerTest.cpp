#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#define exit(code)          \
  throw std::runtime_error( \
      "exit exception")  // redefine exit for testing purposes
#include "../../Group-06/ErrorManager/ErrorManager.hpp"


TEST_CASE("Tests for generic printMessage without line number", "[printMessage]") {
  cse::ErrorManager manager;

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
  manager.enableColors(0);

  SECTION("Two simple strings") {
    buffer.str("");
    manager.printMessage(cse::ErrorManager::ErrorLevel::Info, "hello", " world");
    REQUIRE(buffer.str() == "[Info]: hello world\n");
  }

  SECTION("A string and an int") {
    buffer.str("");
    manager.printMessage(cse::ErrorManager::ErrorLevel::Info, "hello", " world ", 100);
    REQUIRE(buffer.str() == "[Info]: hello world 100\n");
  }

  std::cout.rdbuf(oldCout);
}

TEST_CASE("Tests for generic printMessage with the line number", "[printMessage]") {
  cse::ErrorManager manager;

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
  manager.enableColors(0);

  SECTION("Two simple strings") {
    buffer.str("");
    manager.printMessage(5, cse::ErrorManager::ErrorLevel::Info, "hello", " world");
    REQUIRE(buffer.str() == "[Info] (line 5): hello world\n");
  }

  SECTION("A string and an int") {
    buffer.str("");
    manager.printMessage(5, cse::ErrorManager::ErrorLevel::Info, "hello", " world ", 100);
    REQUIRE(buffer.str() == "[Info] (line 5): hello world 100\n");
  }

  std::cout.rdbuf(oldCout);
}
TEST_CASE("Tests for printMessage messages with color", "[printMessage]") {
  // this resource was used to redirect cout to stringstream:
  // https://truong.io/posts/capturing_stdout_for_c++_unit_testing.html
  cse::ErrorManager manager;

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  SECTION("No ErrorLevel specified (defaults to Info)") {
    buffer.str("");
    manager.printMessage("Default error");
    REQUIRE(buffer.str() == "[\033[32mInfo\033[0m]: Default error\n");
  }

  SECTION("ErrorLevel is info") {
    buffer.str("");
    manager.printMessage("Info error", cse::ErrorManager::ErrorLevel::Info);
    REQUIRE(buffer.str() == "[\033[32mInfo\033[0m]: Info error\n");
  }

  SECTION("ErrorLevel is warning") {
    buffer.str("");
    manager.printMessage("Warning error", cse::ErrorManager::ErrorLevel::Warning);
    REQUIRE(buffer.str() == "[\033[33mWarning\033[0m]: Warning error\n");
  }

  SECTION("ErrorLevel is fatal") {
    buffer.str("");
    manager.printMessage("Fatal error", cse::ErrorManager::ErrorLevel::Fatal);
    REQUIRE(buffer.str() == "[\033[31mFatal\033[0m]: Fatal error\n");
  }

  std::cout.rdbuf(oldCout);
}

TEST_CASE("Tests for printMessage messages without color", "[printMessage]") {
  // this resource was used to redirect cout to stringstream:
  // https://truong.io/posts/capturing_stdout_for_c++_unit_testing.html
  cse::ErrorManager manager;

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  SECTION("No ErrorLevel specified (defaults to Info)") {
    buffer.str("");
    manager.enableColors(false);
    manager.printMessage("Default error");
    REQUIRE(buffer.str() == "[Info]: Default error\n");
  }

  SECTION("ErrorLevel is info") {
    buffer.str("");
    manager.enableColors(false);
    manager.printMessage("Info error", cse::ErrorManager::ErrorLevel::Info);
    REQUIRE(buffer.str() == "[Info]: Info error\n");
  }

  SECTION("ErrorLevel is warning") {
    buffer.str("");
    manager.enableColors(false);
    manager.printMessage("Warning error", cse::ErrorManager::ErrorLevel::Warning);
    REQUIRE(buffer.str() == "[Warning]: Warning error\n");
  }

  SECTION("ErrorLevel is fatal") {
    buffer.str("");
    manager.enableColors(false);
    manager.printMessage("Fatal error", cse::ErrorManager::ErrorLevel::Fatal);
    REQUIRE(buffer.str() == "[Fatal]: Fatal error\n");
  }

  std::cout.rdbuf(oldCout);
}

TEST_CASE("Tests for printMessage with line number overload", "[printMessage]") {
  // this resource was used to redirect cout to stringstream:
  // https://truong.io/posts/capturing_stdout_for_c++_unit_testing.html
  cse::ErrorManager manager;
  manager.enableColors(false);
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
  int32_t lineNumber = 23;

  SECTION("Line number is specified, ErrorLevel is default") {
    buffer.str("");
    manager.printMessage(lineNumber, "Default info error with the line number");
    REQUIRE(buffer.str() ==
            "[Info] (line 23): Default info error with the line number\n");
  }

  SECTION("Both line number and ErrorLevel are specified") {
    buffer.str("");
    manager.printMessage(lineNumber, "Warning error with line number specified",
                       cse::ErrorManager::ErrorLevel::Warning);
    REQUIRE(buffer.str() ==
            "[Warning] (line 23): Warning error with line number specified\n");
  }

  std::cout.rdbuf(oldCout);
}

TEST_CASE("Error coloring can be turned on after turning it off",
          "[printMessage]") {
  // this resource was used to redirect cout to stringstream:
  // https://truong.io/posts/capturing_stdout_for_c++_unit_testing.html
  cse::ErrorManager manager;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  SECTION("Colors are turned on despite being turned on already") {
    manager.enableColors(true);
    buffer.str("");
    manager.printMessage("Info error with colors turned on",
                       cse::ErrorManager::ErrorLevel::Info);
    REQUIRE(buffer.str() ==
            "[\033[32mInfo\033[0m]: Info error with colors turned on\n");
  }

  SECTION("Colors are turned off then turned on") {
    manager.enableColors(false);
    buffer.str("");
    manager.printMessage("Info error with colors turned off");
    REQUIRE(buffer.str() == "[Info]: Info error with colors turned off\n");

    manager.enableColors(true);
    buffer.str("");
    manager.printMessage("Info error with colors turned back on");
    REQUIRE(buffer.str() ==
            "[\033[32mInfo\033[0m]: Info error with colors turned back on\n");
  }

  std::cout.rdbuf(oldCout);
}

TEST_CASE("Action for a specific ErrorLevel is invoked", "[setAction]") {
  cse::ErrorManager manager;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
  manager.enableColors(false);

  SECTION("Action is triggered only for a specific ErrorLevel") {
    manager.setAction(cse::ErrorManager::ErrorLevel::Info,
                      []() { std::cout << "Hello from Action\n"; });
    manager.printMessage("Printing info error",
                       cse::ErrorManager::ErrorLevel::Info);
    REQUIRE(buffer.str() == "[Info]: Printing info error\nHello from Action\n");
  }

  SECTION("Action is not triggered for a level it wasn't attached to") {
    manager.setAction(cse::ErrorManager::ErrorLevel::Info,
                      []() { std::cout << "Hello from Action\n"; });
    manager.printMessage("Printing warning error",
                       cse::ErrorManager::ErrorLevel::Warning);
    REQUIRE(buffer.str() == "[Warning]: Printing warning error\n");
  }

  std::cout.rdbuf(oldCout);
}

TEST_CASE("Program terminates with a specific error code",
          "[enableTermination]") {
  cse::ErrorManager manager;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  SECTION("Program exits when a corresponding error is triggered") {
    manager.enableTermination(cse::ErrorManager::ErrorLevel::Info, true, 228);
    manager.enableColors(false);
    try {
      manager.printMessage("Info message", cse::ErrorManager::ErrorLevel::Info);
      FAIL("The program did not terminate when printMessage was called");
    } catch (std::runtime_error& e) {
      REQUIRE(buffer.str() == "[Info]: Info message\n");
      REQUIRE(std::string(e.what()) == "exit exception");
    }
  }
  std::cout.rdbuf(oldCout);
}

TEST_CASE("Program writes errors into a text file", "[printMessage]") {
  const std::string file = "file.log";
  // Assist from ChatGPT: Clear the file before test
  std::ofstream clearFile(file, std::ios::trunc);
  clearFile.close();

  cse::ErrorManager manager(file);
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
  manager.printMessage("Test error message", cse::ErrorManager::ErrorLevel::Info);

  std::ifstream output(file);
  REQUIRE(output.is_open());

  std::stringstream fileOutput;
  fileOutput << output.rdbuf();
  output.close();

  REQUIRE(fileOutput.str() == "[Info]: Test error message\n");

  // remove the file
  std::remove(file.c_str());
  std::cout.rdbuf(oldCout);
}

TEST_CASE("Program correctly handles case when error is thrown",
          "[executeAndHandleError]") {
  cse::ErrorManager manager;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
  manager.enableColors(false);

  std::function<void()> failedFunction = []() {
    throw std::runtime_error("Exception");
  };

  manager.executeAndHandleError(failedFunction, "Function has failed",
                                cse::ErrorManager::ErrorLevel::Info);

  REQUIRE(buffer.str() == "[Info]: Function has failed\n");
  std::cout.rdbuf(oldCout);
}

TEST_CASE("Tests for printInfo", "[printInfo]") {
  // this resource was used to redirect cout to stringstream:
  // https://truong.io/posts/capturing_stdout_for_c++_unit_testing.html
  cse::ErrorManager manager;

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  SECTION("printInfo basic test") {
    buffer.str("");
    manager.enableColors(false);
    manager.printInfo("Info error");
    REQUIRE(buffer.str() == "[Info]: Info error\n");
  }

  SECTION("printInfo test with the line number") {
    buffer.str("");
    manager.enableColors(false);
    manager.printInfo("Info error", 5);
    REQUIRE(buffer.str() == "[Info] (line 5): Info error\n");
  }

  std::cout.rdbuf(oldCout);
}

TEST_CASE("Tests for printWarning", "[printWarning]") {
  // this resource was used to redirect cout to stringstream:
  // https://truong.io/posts/capturing_stdout_for_c++_unit_testing.html
  cse::ErrorManager manager;

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  SECTION("printWarning basic test") {
    buffer.str("");
    manager.enableColors(false);
    manager.printWarning("Warning error");
    REQUIRE(buffer.str() == "[Warning]: Warning error\n");
  }

  SECTION("printWarning test with the line number") {
    buffer.str("");
    manager.enableColors(false);
    manager.printWarning("Warning error", 5);
    REQUIRE(buffer.str() == "[Warning] (line 5): Warning error\n");
  }

  std::cout.rdbuf(oldCout);
}

TEST_CASE("Tests for printError", "[printError]") {
  // this resource was used to redirect cout to stringstream:
  // https://truong.io/posts/capturing_stdout_for_c++_unit_testing.html
  cse::ErrorManager manager;

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  SECTION("printError basic test") {
    buffer.str("");
    manager.enableColors(false);
    manager.printError("Fatal error");
    REQUIRE(buffer.str() == "[Fatal]: Fatal error\n");
  }

  SECTION("printError test with the line number") {
    buffer.str("");
    manager.enableColors(false);
    manager.printError("Fatal error", 5);
    REQUIRE(buffer.str() == "[Fatal] (line 5): Fatal error\n");
  }

  std::cout.rdbuf(oldCout);
}
#undef exit  // undefine exit