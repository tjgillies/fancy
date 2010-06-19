#include "return.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      ReturnStatement::ReturnStatement(Expression* return_expr) :
        _return_expr(return_expr)
      {
      }

      ReturnStatement::~ReturnStatement()
      {
      }

      EXP_TYPE ReturnStatement::type() const
      {
        return EXP_RETURNSTATEMENT;
      }

      FancyObject* ReturnStatement::eval(Scope *scope, Interpreter* interp)
      {
        FancyObject* retval = _return_expr->eval(scope, interp);
        return retval;
      }

    }
  }
}
