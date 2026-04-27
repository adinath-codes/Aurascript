
#pragma once
#include "object.h"
#include <memory>
#include <unordered_map>
using t_Obj_ptr = std::shared_ptr<ObjectOutline>;
class Env {
private:
  std::unordered_map<std::string, t_Obj_ptr> LiteralsDB;

public:
  t_Obj_ptr get(const std::string &literal) { return LiteralsDB.at(literal); }
  t_Obj_ptr set(const std::string &literal, t_Obj_ptr ObjPtr) {
    LiteralsDB[literal] = ObjPtr;
    return ObjPtr;
  }
};
