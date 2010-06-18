#include "nil.h"
#include "string.h"
#include "bootstrap/core_classes.h"

namespace fancy {

  Nil::Nil() : FancyObject(NilClass) {}

  Nil::~Nil() {}

  FancyObject* Nil::equal(FancyObject* other) const
  {
    if(IS_NIL(other))
      return t;
    return nil;
  }

  FancyObject* Nil::eval(Scope *scope)
  {
    return nil;
  }

  EXP_TYPE Nil::type() const
  {
    return EXP_NIL;
  }

  const FancyString Nil::to_s() const
  {
    return FancyString("nil");
  }

}
