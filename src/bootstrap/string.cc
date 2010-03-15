#include "includes.h"

void init_string_class()
{  
  StringClass->def_method("downcase", new NativeMethod("downcase", method_String_downcase));
  StringClass->def_method("upcase", new NativeMethod("upcase", method_String_upcase));
  StringClass->def_method("from:to:", new NativeMethod("from:to:", method_String_from__to));
}


/**
 * String instance methods
 */

FancyObject_p method_String_downcase(FancyObject_p self, list<Expression_p> args, Scope *scope)
{
  if(args.size() > 0) {
    errorln("String#downcase got more than 0 arguments!");
  } else {
    if(IS_STRING(self->native_value())) {
      string str = dynamic_cast<String_p>(self->native_value())->value();
      std::transform(str.begin(), str.end(), str.begin(), ::tolower);
      return StringClass->create_instance(String::from_value(str));
    } else {
      return nil;
    }
  }
  return nil;
}

FancyObject_p method_String_upcase(FancyObject_p self, list<Expression_p> args, Scope *scope)
{
  if(args.size() > 0) {
    errorln("String#upcase got more than 0 arguments!");
  } else {
    if(IS_STRING(self->native_value())) {
      string str = dynamic_cast<String_p>(self->native_value())->value();
      std::transform(str.begin(), str.end(), str.begin(), ::toupper);
      return StringClass->create_instance(String::from_value(str));
    } else {
      return nil;
    }
  }
  return nil;
}

FancyObject_p method_String_from__to(FancyObject_p self, list<Expression_p> args, Scope *scope)
{
  if(args.size() != 2) {
    error("String#to:from: expected 2 arguments, but got: ") << args.size() << endl;
  } else {
    if(IS_STRING(self->native_value())) {
      string str = dynamic_cast<String_p>(self->native_value())->value();

      FancyObject_p arg1 = args.front()->eval(scope);
      args.pop_front();
      FancyObject_p arg2 = args.front()->eval(scope);

      if(IS_INT(arg1->native_value()) && IS_INT(arg2->native_value())) {
        Number_p idx1 = dynamic_cast<Number_p>(arg1->native_value());
        Number_p idx2 = dynamic_cast<Number_p>(arg2->native_value());
        string substr = str.substr(idx1->intval(), idx2->intval() - idx1->intval());
        return StringClass->create_instance(String::from_value(substr));
      } else {
        errorln("String#to:from: expects 2 Integer arguments");
        return self;
      }
    } else {
      return nil;
    }
  }
  return nil;
}