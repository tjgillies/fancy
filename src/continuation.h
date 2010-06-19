#ifndef _CONTINUATION_H_
#define _CONTINUATION_H_

#include "block.h"
#include "scope.h"
#include "callable.h"

namespace fancy {

  class Continuation : public FancyObject, public Callable
  {
  public:
    Continuation(Block* body_block, Scope* activation_scope);
    virtual ~Continuation() {}

    virtual FancyObject* call(FancyObject *self, FancyObject** args, int argc, Scope *scope, Interpreter* interp);
    virtual FancyObject* call(FancyObject *self, Scope *scope, Interpreter* interp);

    FancyObject* run(Interpreter* interp);

    Scope* activation_scope() const { return _activation_scope; }

  private:
    Block* _body_block;
    Scope* _activation_scope;
  };

}

#endif /* _CONTINUATION_H_ */
