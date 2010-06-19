#include "continuation.h"
#include <iostream>

#include "bootstrap/core_classes.h"

namespace fancy {

  Continuation::Continuation(Block* body_block, Scope* activation_scope) :
    FancyObject(ContinuationClass),
    _body_block(body_block),
    _activation_scope(activation_scope)
  {
  }

  FancyObject* Continuation::call(FancyObject *self, FancyObject** args, int argc, Scope *scope, Interpreter* interp)
  {
    return nil;
  }

  FancyObject* Continuation::call(FancyObject *self, Scope *scope, Interpreter* interp)
  {
    return nil;
  }

  FancyObject* Continuation::run(Interpreter* interp)
  {
    FancyObject* arg = this;
    return _body_block->call(_activation_scope->current_self(), &arg, 1, _activation_scope, interp);
  }
}
