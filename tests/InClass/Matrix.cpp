#include "../../third-party/Catch/single_include/catch2/catch.hpp"

#include "../../InClass/Group-00/Matrix.hpp"

TEST_CASE("Test cse::Matrix", "[base]")
{
  cse::Matrix<int> m1;
  cse::Matrix<int> m2(10,10);
  cse::Matrix<int> m3(1,1000);

  CHECK(m1.NumRows() == 0);
  CHECK(m1.NumCols() == 0);
  CHECK(m1.NumCells() == 0);

  CHECK(m2.NumRows() == 10);
  CHECK(m2.NumCols() == 10);
  CHECK(m2.NumCells() == 100);

  CHECK(m3.NumRows() == 1);
  CHECK(m3.NumCols() == 1000);
  CHECK(m3.NumCells() == 1000);

  m1.Resize(3,3,-7);
  CHECK(m1.NumRows() == 3);
  CHECK(m1.NumCols() == 3);
  CHECK(m1.NumCells() == 9);

  m1.At(0,1) = 12;
  m1.At(2,2) = 30;

  const cse::Matrix<int> m4 = m1;
  CHECK(m1.At(0,1) == 12);
  CHECK(m1.At(2,2) == 30);
  CHECK(m4.At(0,1) == 12);
  CHECK(m4.At(2,2) == 30);

  m1[0][0] = 106;
  m1[2][0] = 1;

  CHECK(m1.At(0,0) == 106);
  CHECK(m1.At(2,0) == 1);


  // m1[1,0] = 15;
  m1.At(1,0) = 15;

  CHECK(m1.At(0,0) == 106);
  CHECK(m1.At(0,1) == 12);
  CHECK(m1.At(0,2) == -7);
}
