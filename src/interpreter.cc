#include "interpreter.h"
#include "parser/parser.h"

namespace fancy {

  Interpreter::Interpreter(parser::nodes::expression_node* expressions, Scope* initial_scope) :
    _expressions(expressions),
    _current_expr(expressions),
    _current_scope(initial_scope)
  {
  }

  void Interpreter::run()
  {
    for(parser::nodes::expression_node* tmp = _expressions;
        tmp != NULL;
        tmp = tmp->next) {
      fancy::parser::last_value = tmp->expression->eval(_current_scope, this);
    }
  }
}
