#pragma once
#include <string>
enum class OBJECT_TYPES { INTEGER_OBJ, BOOL_OBJ, STRING_OBJ, NULL_OBJ };

class ObjectOutline {
public:
  virtual OBJECT_TYPES type() = 0;
  virtual std::string viewValue() = 0;
  virtual ~ObjectOutline() = default;
};

class IntObject : public ObjectOutline {
public:
  long long value;
  IntObject(long long v) : value(v) {}
  OBJECT_TYPES type() override { return OBJECT_TYPES::INTEGER_OBJ; }
  std::string viewValue() override {
    return std::to_string(value); // TODO: OPTIMISE
  }
};

class BoolObject : public ObjectOutline {
public:
  bool value;
  BoolObject(bool v) : value(v) {}
  OBJECT_TYPES type() override { return OBJECT_TYPES::BOOL_OBJ; }
  std::string viewValue() override { return value ? "nocap" : "cap"; }
};

class StringObject : public ObjectOutline {
public:
  std::string value;
  StringObject(std::string v) : value(v) {}
  OBJECT_TYPES type() override { return OBJECT_TYPES::STRING_OBJ; }
  std::string viewValue() override { return value; }
};

class NullObject : public ObjectOutline {
public:
  OBJECT_TYPES type() override { return OBJECT_TYPES::NULL_OBJ; }
  std::string viewValue() override { return "NULL"; }
};
