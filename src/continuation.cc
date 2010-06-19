#include "continuation.h"
#include "interpreter.h"
#include "bootstrap/core_classes.h"

namespace fancy {

  Continuation::Continuation(Block* body_block, Scope* activation_scope) :
    FancyObject(ContinuationClass),
    _body_block(body_block),
    _activation_scope(activation_scope->clone())
  {
  }

  FancyObject* Continuation::call(FancyObject *self, FancyObject** args, int argc, Scope *scope, Interpreter* interp)
  {
    interp->activate_contination(this);
    return args[0];
  }

  FancyObject* Continuation::call(FancyObject *self, Scope *scope, Interpreter* interp)
  {
    return nil;
  }

  FancyObject* Continuation::run(Interpreter* interp)
  {
    interp->set_continuation_marker(this); 
    FancyObject* arg = this;
    return _body_block->call(_activation_scope->current_self(), &arg, 1, _activation_scope, interp);
  }
}
