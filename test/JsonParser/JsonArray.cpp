// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("deserializeJson(JsonArray&)") {
  DynamicJsonArray arr;

  SECTION("EmptyArray") {
    JsonError err = deserializeJson(arr, "[]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(0 == arr.size());
  }

  SECTION("MissingOpeningBracket") {
    JsonError err = deserializeJson(arr, "]");
    REQUIRE_FALSE(err == JsonError::Ok);
  }

  SECTION("ArrayWithNoEnd") {
    JsonError err = deserializeJson(arr, "[");
    REQUIRE_FALSE(err == JsonError::Ok);
  }

  SECTION("EmptyArrayWithLeadingSpaces") {
    JsonError err = deserializeJson(arr, "  []");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(0 == arr.size());
  }

  SECTION("Garbage") {
    JsonError err = deserializeJson(arr, "%*$£¤");

    REQUIRE_FALSE(err == JsonError::Ok);
  }

  SECTION("OneInteger") {
    JsonError err = deserializeJson(arr, "[42]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == 42);
  }

  SECTION("OneIntegerWithSpacesBefore") {
    JsonError err = deserializeJson(arr, "[ \t\r\n42]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == 42);
  }

  SECTION("OneIntegerWithSpaceAfter") {
    JsonError err = deserializeJson(arr, "[42 \t\r\n]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == 42);
  }

  SECTION("TwoIntegers") {
    JsonError err = deserializeJson(arr, "[42,84]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == 42);
    REQUIRE(arr[1] == 84);
  }

  SECTION("TwoDoubles") {
    JsonError err = deserializeJson(arr, "[4.2,1e2]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == 4.2);
    REQUIRE(arr[1] == 1e2);
  }

  SECTION("UnsignedLong") {
    JsonError err = deserializeJson(arr, "[4294967295]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == 4294967295UL);
  }

  SECTION("TwoBooleans") {
    JsonError err = deserializeJson(arr, "[true,false]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == true);
    REQUIRE(arr[1] == false);
  }

  SECTION("TwoNulls") {
    JsonError err = deserializeJson(arr, "[null,null]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0].as<char *>() == 0);
    REQUIRE(arr[1].as<char *>() == 0);
  }

  SECTION("TwoStringsDoubleQuotes") {
    JsonError err = deserializeJson(arr, "[ \"hello\" , \"world\" ]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == "hello");
    REQUIRE(arr[1] == "world");
  }

  SECTION("TwoStringsSingleQuotes") {
    JsonError err = deserializeJson(arr, "[ 'hello' , 'world' ]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == "hello");
    REQUIRE(arr[1] == "world");
  }

  SECTION("TwoStringsNoQuotes") {
    JsonError err = deserializeJson(arr, "[ hello , world ]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == "hello");
    REQUIRE(arr[1] == "world");
  }

  SECTION("EmptyStringsDoubleQuotes") {
    JsonError err = deserializeJson(arr, "[\"\",\"\"]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == "");
    REQUIRE(arr[1] == "");
  }

  SECTION("EmptyStringSingleQuotes") {
    JsonError err = deserializeJson(arr, "[\'\',\'\']");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == "");
    REQUIRE(arr[1] == "");
  }

  SECTION("EmptyStringNoQuotes") {
    JsonError err = deserializeJson(arr, "[,]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == "");
    REQUIRE(arr[1] == "");
  }

  SECTION("ClosingDoubleQuoteMissing") {
    JsonError err = deserializeJson(arr, "[\"]");

    REQUIRE_FALSE(err == JsonError::Ok);
  }

  SECTION("ClosingSignleQuoteMissing") {
    JsonError err = deserializeJson(arr, "[\']");

    REQUIRE_FALSE(err == JsonError::Ok);
  }

  SECTION("StringWithEscapedChars") {
    JsonError err =
        deserializeJson(arr, "[\"1\\\"2\\\\3\\/4\\b5\\f6\\n7\\r8\\t9\"]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == "1\"2\\3/4\b5\f6\n7\r8\t9");
  }

  SECTION("StringWithUnterminatedEscapeSequence") {
    JsonError err = deserializeJson(arr, "\"\\\0\"", 4);
    REQUIRE_FALSE(err == JsonError::Ok);
  }

  SECTION("CCommentBeforeOpeningBracket") {
    JsonError err = deserializeJson(arr, "/*COMMENT*/  [\"hello\"]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == "hello");
  }

  SECTION("CCommentAfterOpeningBracket") {
    JsonError err = deserializeJson(arr, "[/*COMMENT*/ \"hello\"]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == "hello");
  }

  SECTION("CCommentBeforeClosingBracket") {
    JsonError err = deserializeJson(arr, "[\"hello\"/*COMMENT*/]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == "hello");
  }

  SECTION("CCommentAfterClosingBracket") {
    JsonError err = deserializeJson(arr, "[\"hello\"]/*COMMENT*/");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == "hello");
  }

  SECTION("CCommentBeforeComma") {
    JsonError err = deserializeJson(arr, "[\"hello\"/*COMMENT*/,\"world\"]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == "hello");
    REQUIRE(arr[1] == "world");
  }

  SECTION("CCommentAfterComma") {
    JsonError err = deserializeJson(arr, "[\"hello\",/*COMMENT*/ \"world\"]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == "hello");
    REQUIRE(arr[1] == "world");
  }

  SECTION("CppCommentBeforeOpeningBracket") {
    JsonError err = deserializeJson(arr, "//COMMENT\n\t[\"hello\"]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == "hello");
  }

  SECTION("CppCommentAfterOpeningBracket") {
    JsonError err = deserializeJson(arr, "[//COMMENT\n\"hello\"]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == "hello");
  }

  SECTION("CppCommentBeforeClosingBracket") {
    JsonError err = deserializeJson(arr, "[\"hello\"//COMMENT\r\n]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == "hello");
  }

  SECTION("CppCommentAfterClosingBracket") {
    JsonError err = deserializeJson(arr, "[\"hello\"]//COMMENT\n");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(arr[0] == "hello");
  }

  SECTION("CppCommentBeforeComma") {
    JsonError err = deserializeJson(arr, "[\"hello\"//COMMENT\n,\"world\"]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == "hello");
    REQUIRE(arr[1] == "world");
  }

  SECTION("CppCommentAfterComma") {
    JsonError err = deserializeJson(arr, "[\"hello\",//COMMENT\n\"world\"]");

    REQUIRE(err == JsonError::Ok);
    REQUIRE(2 == arr.size());
    REQUIRE(arr[0] == "hello");
    REQUIRE(arr[1] == "world");
  }

  SECTION("InvalidCppComment") {
    JsonError err = deserializeJson(arr, "[/COMMENT\n]");
    REQUIRE_FALSE(err == JsonError::Ok);
  }

  SECTION("InvalidComment") {
    JsonError err = deserializeJson(arr, "[/*/\n]");
    REQUIRE_FALSE(err == JsonError::Ok);
  }

  SECTION("UnfinishedCComment") {
    JsonError err = deserializeJson(arr, "[/*COMMENT]");
    REQUIRE_FALSE(err == JsonError::Ok);
  }

  SECTION("EndsInCppComment") {
    JsonError err = deserializeJson(arr, "[//COMMENT");
    REQUIRE_FALSE(err == JsonError::Ok);
  }

  SECTION("AfterClosingStar") {
    JsonError err = deserializeJson(arr, "[/*COMMENT*");
    REQUIRE_FALSE(err == JsonError::Ok);
  }

  SECTION("DeeplyNested") {
    JsonError err = deserializeJson(
        arr, "[[[[[[[[[[[[[[[[[[[\"Not too deep\"]]]]]]]]]]]]]]]]]]]");
    REQUIRE(err == JsonError::Ok);
  }

  SECTION("ObjectNestedInArray") {
    char jsonString[] =
        " [ { \"a\" : 1 , \"b\" : 2 } , { \"c\" : 3 , \"d\" : 4 } ] ";

    JsonError err = deserializeJson(arr, jsonString);

    JsonObject &object1 = arr[0];
    const JsonObject &object2 = arr[1];
    JsonObject &object3 = arr[2];

    REQUIRE(err == JsonError::Ok);

    REQUIRE(true == object1.success());
    REQUIRE(true == object2.success());
    REQUIRE(false == object3.success());

    REQUIRE(2 == object1.size());
    REQUIRE(2 == object2.size());
    REQUIRE(0 == object3.size());

    REQUIRE(1 == object1["a"].as<int>());
    REQUIRE(2 == object1["b"].as<int>());
    REQUIRE(3 == object2["c"].as<int>());
    REQUIRE(4 == object2["d"].as<int>());
    REQUIRE(0 == object3["e"].as<int>());
  }
}
