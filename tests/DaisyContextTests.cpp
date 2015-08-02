/**
 * Copyright (c) 2015 by Kota Iguchi. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
#include "gtest/gtest.h"

#define XCTAssertEqual    ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue     ASSERT_TRUE
#define XCTAssertFalse    ASSERT_FALSE

#include "Daisy/daisy.hpp"

using namespace Daisy;

TEST(DaisyContextTests, ContextInit) {
  JSContextGroup js_context_group;
  auto js_context1 = js_context_group.CreateContext();
  auto js_context2 = js_context_group.CreateContext();
  // There's only one context in Daisy
  XCTAssertTrue(js_context1 == js_context2);
}

TEST(DaisyContextTests, UIntNumberInit) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_number = js_context.CreateNumber(1234);
  XCTAssertEqual(1234, static_cast<std::uint32_t>(js_number));
  XCTAssertTrue(js_number.IsNumber());
}

TEST(DaisyContextTests, IntNumberInit) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_number = js_context.CreateNumber(-1234);
  XCTAssertEqual(-1234, static_cast<std::int32_t>(js_number));
  XCTAssertTrue(js_number.IsNumber());
}

TEST(DaisyContextTests, DoubleNumberInit) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_number = js_context.CreateNumber(1234.5);
  XCTAssertEqual(1234.5, static_cast<double>(js_number));
  XCTAssertTrue(js_number.IsNumber());
}

TEST(DaisyContextTests, BooleanInit) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_bool = js_context.CreateBoolean(true);
  XCTAssertEqual(true, static_cast<bool>(js_bool));
  XCTAssertTrue(js_bool.IsBoolean());
}

TEST(DaisyContextTests, StringInit) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_string = js_context.CreateString("StringInit Test");
  XCTAssertEqual("StringInit Test", static_cast<std::string>(js_string));
  XCTAssertTrue(js_string.IsString());

  auto js_string_copy = js_string;
  XCTAssertEqual(js_string, js_string_copy);
  XCTAssertEqual("StringInit Test", static_cast<std::string>(js_string_copy));
  XCTAssertTrue(js_string_copy.IsString());

  auto js_value = static_cast<JSValue>(js_string);
  XCTAssertTrue(js_value.IsString());
  XCTAssertEqual("StringInit Test", static_cast<std::string>(js_value));
  XCTAssertTrue(js_value == js_string);
}

TEST(DaisyContextTests, ObjectInit) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_object = js_context.CreateObject();
  XCTAssertTrue(js_object.IsObject());
  auto js_object_copy = js_object;
  XCTAssertTrue(js_object == js_object_copy);
}

TEST(DaisyContextTests, JSEvaluateScriptString) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_value = js_context.JSEvaluateScript("'Hello, World!';");
  XCTAssertTrue(js_value.IsString());
  XCTAssertEqual("Hello, World!", static_cast<std::string>(js_value));
}

TEST(DaisyContextTests, JSEvaluateScriptBool) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_value = js_context.JSEvaluateScript("true;");
  XCTAssertTrue(js_value.IsBoolean());
  XCTAssertEqual(true, static_cast<bool>(js_value));
}

TEST(DaisyContextTests, JSEvaluateScriptNumber) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_value = js_context.JSEvaluateScript("1234.5;");
  XCTAssertTrue(js_value.IsNumber());
  XCTAssertEqual(1234.5, static_cast<double>(js_value));
}

TEST(DaisyContextTests, JSEvaluateScriptFunction) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_value = js_context.JSEvaluateScript("function a() { return 1234.5; } a();");
  XCTAssertTrue(js_value.IsNumber());
  XCTAssertEqual(1234.5, static_cast<double>(js_value));
}

TEST(DaisyContextTests, JSEvaluateScriptCallAsFunction) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_value = js_context.JSEvaluateScript("function a() { return 1234.5; };a;");
  XCTAssertTrue(js_value.IsObject());
  auto js_object = static_cast<JSObject>(js_value);
  XCTAssertTrue(js_object.IsFunction());
  auto js_result = js_object();
  XCTAssertEqual(1234.5, static_cast<double>(js_result));
}

TEST(DaisyContextTests, BooleanCast) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_bool = js_context.CreateBoolean(true);
  XCTAssertEqual("true", static_cast<std::string>(js_bool));
}

TEST(DaisyContextTests, DoubleCast) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_number = js_context.CreateNumber(1234.5);
  XCTAssertEqual("1234.5", static_cast<std::string>(js_number));
}

TEST(DaisyContextTests, NullCast) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_value = js_context.CreateNull();
  XCTAssertEqual("null", static_cast<std::string>(js_value));
}

TEST(DaisyContextTests, UndefinedCast) {
  JSContextGroup js_context_group;
  auto js_context = js_context_group.CreateContext();
  auto js_value = js_context.CreateUndefined();
  XCTAssertEqual("undefined", static_cast<std::string>(js_value));
}