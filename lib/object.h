#pragma once
#include "lexer.h"
#include <memory>
#include <string>

enum class OBJECT_TYPES {
  INTEGER_OBJ,
  BOOL_OBJ,
  STRING_OBJ,
  NULL_OBJ,
  INFIX_OBJ,
  IDENT_OBJ,
  YAP_STATEMENT,
  LOWKEY_STATEMENT
};

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
  std::string viewValue() override { return value ? "true" : "false"; }
};

class StringObject : public ObjectOutline {
public:
  std::string value;
  StringObject(std::string v) : value(v) {}
  OBJECT_TYPES type() override { return OBJECT_TYPES::STRING_OBJ; }
  std::string viewValue() override { return value; }
};

class IdentObject : public ObjectOutline {
public:
  std::string value;
  IdentObject(std::string v) : value(v) {}
  OBJECT_TYPES type() override { return OBJECT_TYPES::IDENT_OBJ; }
  std::string viewValue() override { return value; }
};

class NullObject : public ObjectOutline {
public:
  OBJECT_TYPES type() override { return OBJECT_TYPES::NULL_OBJ; }
  std::string viewValue() override { return "NULL"; }
};

class InfixNode : public ObjectOutline {
public:
  std::string Operator;
  TokenTypes operatorType;
  std::shared_ptr<ObjectOutline> Left;
  std::shared_ptr<ObjectOutline> Right;
  OBJECT_TYPES type() override { return OBJECT_TYPES::INFIX_OBJ; }
  std::string viewValue() override {
    return Left->viewValue() + " " + Operator + " " + Right->viewValue();
  }
};

// exterm centrally defines them so no reductancy on multiple call
extern const std::shared_ptr<NullObject> GLOBAL_NULL_OBJ;
extern const std::shared_ptr<BoolObject> GLOBAL_TRUE_OBJ;
extern const std::shared_ptr<BoolObject> GLOBAL_FALSE_OBJ;