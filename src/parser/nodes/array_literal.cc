#include "array_literal.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      ArrayLiteral::ArrayLiteral(expression_node *expr_list)
      {
        for(expression_node *tmp = expr_list; tmp != NULL; tmp = tmp->next) {
          _expressions.push_front(tmp->expression);
        }
      }

      ArrayLiteral::~ArrayLiteral()
      {
      }

      FancyObject* ArrayLiteral::eval(Scope *scope, Interpreter* interp)
      {
        vector<FancyObject*> values;
        for(list<Expression*>::iterator it = _expressions.begin();
            it != _expressions.end();
            it++) {
          values.push_back((*it)->eval(scope, interp));
        }
        return new Array(values);
      }

      EXP_TYPE ArrayLiteral::type() const
      {
        return EXP_ARRAYLITERAL;
      }

    }
  }
}
