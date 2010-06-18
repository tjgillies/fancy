#include "true.h"
#include "string.h"
#include "bootstrap/core_classes.h"

namespace fancy {

  True::True() : FancyObject(TrueClass) {}

  True::~True() {}

  FancyObject* True::equal(FancyObject* other) const
  {
    if(IS_TRUE(other))
      return t;
    return nil;
  }

  FancyObject* True::eval(Scope *scope)
  {
    return t;
  }

  EXP_TYPE True::type() const
  {
    return EXP_TRUE;
  }

  const FancyString True::to_s() const
  {
    return FancyString("true");
  }

}
