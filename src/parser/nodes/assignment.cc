#include <map>

#include "assignment.h"
#include "../../scope.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      AssignmentExpr::AssignmentExpr(Identifier* identifier, Expression* value_expr) :
        _identifier(identifier), _value_expr(value_expr)
      {
      }

      AssignmentExpr::~AssignmentExpr()
      {
      }

      EXP_TYPE AssignmentExpr::type() const
      {
        return EXP_ASSIGNEXPR;
      }

      FancyObject* AssignmentExpr::eval(Scope *scope, Interpreter* interp)
      {
        FancyObject* value = _value_expr->eval(scope, interp);
        scope->define(_identifier->name(), value);
        return value;
      }

    }
  }
}
