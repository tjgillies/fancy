#include "super.h"
#include "../../bootstrap/core_classes.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      Super::Super()
      {
      }

      Super::~Super()
      {
      }
      
      FancyObject* Super::eval(Scope *scope, Interpreter* interp)
      {
        // we simply return nil, since this value isn't needed.
        // see MethodCall#eval() for dealing with super method calls.
        return nil;
      }

      EXP_TYPE Super::type() const
      {
        return EXP_SUPER;
      }

    }
  }
}
