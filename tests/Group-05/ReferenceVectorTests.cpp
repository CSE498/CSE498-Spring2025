/**
 * @file ReferenceVectorTests.cpp
 *
 * @author Calen Green and Max Krawec
 *
 * Tests for the ReferenceVector class.
 */

#include "../../Group-05/src/Datum.cpp"

#include "../../Group-05/src/ReferenceVector.h"

#include "../../third-party/Catch/single_include/catch2/catch.hpp"

TEST_CASE("PushBack() functionality", "[push_back]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);
  cse::ReferenceVector<cse::Datum> reference_vector;

  reference_vector.PushBack(d1);
  reference_vector.PushBack(d2);
  reference_vector.PushBack(d3);

  CHECK(reference_vector.Size() == 3);
}

TEST_CASE("PopBack() functionality", "[pop_back]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);
  cse::ReferenceVector<cse::Datum> reference_vector;

  reference_vector.PushBack(d1);
  reference_vector.PushBack(d2);
  reference_vector.PushBack(d3);
  reference_vector.PopBack();

  CHECK(reference_vector.Size() == 2);

  cse::ReferenceVector<cse::Datum> empty;
  CHECK_THROWS(empty.PopBack());
}

TEST_CASE("Size() functionality", "[size]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);
  cse::ReferenceVector<cse::Datum> reference_vector;

  reference_vector.PushBack(d1);
  reference_vector.PushBack(d2);
  reference_vector.PushBack(d3);

  CHECK(reference_vector.Size() == 3);
}

TEST_CASE("Empty() functionality", "[empty]") {
  cse::ReferenceVector<cse::Datum> reference_vector;
  CHECK(reference_vector.Empty());

  cse::Datum d1(123.123);
  reference_vector.PushBack(d1);

  CHECK(!reference_vector.Empty());
}

TEST_CASE("Clear() functionality", "[clear]") {
  cse::ReferenceVector<cse::Datum> reference_vector;
  cse::Datum d1(123.123);
  reference_vector.PushBack(d1);

  reference_vector.Clear();

  CHECK(reference_vector.Empty());
}

TEST_CASE("Element access functionality", "[access]") {
  cse::Datum d1(123.123);
  cse::Datum d2(987);
  cse::ReferenceVector<cse::Datum> reference_vector;

  reference_vector.PushBack(d1);
  reference_vector.PushBack(d2);

  CHECK(reference_vector.Front().GetDouble() == 123.123);
  CHECK(reference_vector.Back().GetDouble() == 987);

  cse::ReferenceVector<cse::Datum> empty;
  CHECK_THROWS(empty.Front());
  CHECK_THROWS(empty.Back());
}

TEST_CASE("Erase() functionality", "[erase]") {

  SECTION("Single index erase") {
    cse::Datum d1(123.123);
    cse::Datum d2("test");
    cse::Datum d3(987);
    cse::ReferenceVector<cse::Datum> reference_vector;

    reference_vector.PushBack(d1);
    reference_vector.PushBack(d2);
    reference_vector.PushBack(d3);

    reference_vector.Erase(0);
    CHECK(reference_vector.Front().GetString() == "test");

    reference_vector.Erase(1);
    CHECK(reference_vector.Front().GetString() == "test");
  }

  SECTION("Multiple indices erase") {
    cse::Datum d1(123.123);
    cse::Datum d2("test");
    cse::Datum d3(987);
    cse::ReferenceVector<cse::Datum> reference_vector;

    reference_vector.PushBack(d1);
    reference_vector.PushBack(d2);
    reference_vector.PushBack(d3);

    SECTION("Remove all indices") {
      reference_vector.EraseIndices(0, 3);
      CHECK(reference_vector.Empty());
    }

    SECTION("Remove a few indices") {
      reference_vector.EraseIndices(0,2);
      CHECK(reference_vector.Size() == 1);
    }
  }

  SECTION("Invalid Erases") {
    cse::ReferenceVector<cse::Datum> empty;
    CHECK_THROWS(empty.Erase(1));
    CHECK_THROWS(empty.EraseIndices(2,7));

    cse::Datum d1(123.123);
    cse::Datum d2("test");
    cse::ReferenceVector<cse::Datum> values;

    values.PushBack(d1);
    values.PushBack(d2);
    CHECK_THROWS(empty.EraseIndices(1,0));
  }
}

TEST_CASE("Insert() functionality", "[insert]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);
  cse::ReferenceVector<cse::Datum> reference_vector;

  reference_vector.PushBack(d1);
  reference_vector.PushBack(d2);
  reference_vector.PushBack(d3);

  cse::Datum d4("apple");
  reference_vector.Insert(1, d4);

  CHECK(reference_vector.At(1).GetString() == "apple");
  CHECK(reference_vector.At(2).GetString() == "test");
  CHECK(reference_vector.Size() == 4);

  cse::ReferenceVector<cse::Datum> empty;
  CHECK_THROWS(empty.Insert(2, d3));
  CHECK_THROWS(empty[1] = d3);
}

TEST_CASE("Element modification functionality", "[modify]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);
  cse::Datum new_datum("hello");
  cse::Datum new_datum1("UpdatedDatum");
  cse::Datum new_datum2(987.987);

  cse::ReferenceVector<cse::Datum> reference_vector;
  reference_vector.PushBack(d1);
  reference_vector.PushBack(d2);
  reference_vector.PushBack(d3);

  reference_vector[0] = new_datum;
  reference_vector[1] = new_datum1;
  reference_vector[2] = new_datum2;

  CHECK(reference_vector.At(0).GetString() == "hello");
  CHECK(reference_vector.At(1).GetString() == "UpdatedDatum");
  CHECK(reference_vector.At(2).GetDouble() == 987.987);

  cse::ReferenceVector<cse::Datum> empty;
  CHECK_THROWS(empty.At(1));

  CHECK(reference_vector[0].GetString() == "hello");
  CHECK(reference_vector[1].GetString() == "UpdatedDatum");
  CHECK(reference_vector[2].GetDouble() == 987.987);
}

TEST_CASE("SetReference() functionality", "[set_reference]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);

  cse::ReferenceVector<cse::Datum> reference_vector;
  reference_vector.PushBack(d1);
  reference_vector.PushBack(d2);
  reference_vector.PushBack(d3);

  cse::Datum d4("happy");
  reference_vector.SetReference(0, d4);
  CHECK(reference_vector[0].GetString() == "happy");

  d4 = "sad";
  CHECK(reference_vector[0].GetString() == "sad");

  cse::ReferenceVector<cse::Datum> empty;
  CHECK_THROWS(empty.SetReference(2, d3));
}

TEST_CASE("Iterator functionality", "[iterator]") {
  cse::Datum d1(123.123);
  cse::Datum d2("test");
  cse::Datum d3(987);

  cse::ReferenceVector<cse::Datum> reference_vector;
  reference_vector.PushBack(d1);
  reference_vector.PushBack(d2);
  reference_vector.PushBack(d3);

  SECTION("Iterator traversal") {
    auto it = reference_vector.begin();
    CHECK((*it).GetDouble() == 123.123);

    ++it;
    CHECK((*it).GetString() == "test");

    ++it;
    CHECK((*it).GetDouble() == 987);

    ++it;
    CHECK(it == reference_vector.end());
  }

  SECTION("Reverse iterator traversal") {
    auto it = reference_vector.end();
    
    --it;
    CHECK((*it).GetDouble() == 987);

    --it;
    CHECK((*it).GetString() == "test");

    --it;
    CHECK((*it).GetDouble() == 123.123);

    CHECK(it == reference_vector.begin());
  }
}