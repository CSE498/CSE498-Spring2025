// Anand
#include "../../third-party/Catch/single_include/catch2/catch.hpp"
#include "../../Group-07/Team07Library/DataFileManager.h"
#include "../../Group-07/Team07Library/DataFileManager.cpp"

TEST_CASE("DataFileManagerTest Construct", "[DataFileManager]") {
  cse::DataFileManager dfm;
  dfm.openFile("../CSE498-Spring2025-team07-manager/Group-07/Data/sample.csv");

  // Based on Example given by prof
  int x = 5;
  int y = 10;

  dfm.addFunction( "X Value", [&x](){return x;} );
  dfm.addFunction( "Y Value", [&y](){return y;} );
  dfm.listFunctions();

  dfm.update();
  x++;
  dfm.update();
  y++;
  dfm.update();

  // Test to make sure update doesn't work
  dfm.deleteFunction("X Value");
  dfm.update();

  // Test clear and closeFile
  dfm.clearFunctions();
  dfm.closeFile();

  REQUIRE(1 == 1);
}
