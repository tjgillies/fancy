#include "interpreter.h"
#include "parser/parser.h"

namespace fancy {

  Interpreter::Interpreter(parser::nodes::expression_node* expressions, Scope* initial_scope) :
    _expressions(expressions),
    _current_expr(expressions),
    _current_scope(initial_scope)
  {
    _expr_count = 0;
    for(parser::nodes::expression_node* tmp = expressions; tmp; tmp = tmp->next) {
      _expr_count++;
    }
  }

  void Interpreter::run()
  {
    for(_current_expr = _expressions;
        _current_expr != NULL;
        _current_expr = _current_expr->next) {
      fancy::parser::last_value = _current_expr->expression->eval(_current_scope, this);
    }
  }
}
