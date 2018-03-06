// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

void testStringification(JsonError error, std::string expected) {
  REQUIRE(error.c_str() == expected);
}

void testBoolification(JsonError error, bool expected) {
  CHECK(error == expected);
}

#define TEST_STRINGIFICATION(symbol) \
  testStringification(JsonError::symbol, #symbol)

#define TEST_BOOLIFICATION(symbol, expected) \
  testBoolification(JsonError::symbol, expected)

TEST_CASE("JsonError") {
  SECTION("c_str()") {
    TEST_STRINGIFICATION(Ok);
    TEST_STRINGIFICATION(OpeningBraceExpected);
    TEST_STRINGIFICATION(ClosingBraceExpected);
    TEST_STRINGIFICATION(MissingBracket);
    TEST_STRINGIFICATION(ColonExpected);
    TEST_STRINGIFICATION(MissingComma);
    TEST_STRINGIFICATION(TooDeep);
    TEST_STRINGIFICATION(NoMemory);
  }

  SECTION("as boolean") {
    TEST_BOOLIFICATION(Ok, false);
    TEST_BOOLIFICATION(OpeningBraceExpected, true);
    TEST_BOOLIFICATION(ClosingBraceExpected, true);
    TEST_BOOLIFICATION(MissingBracket, true);
    TEST_BOOLIFICATION(ColonExpected, true);
    TEST_BOOLIFICATION(MissingComma, true);
    TEST_BOOLIFICATION(TooDeep, true);
    TEST_BOOLIFICATION(NoMemory, true);
  }
}
