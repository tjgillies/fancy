#include "interpreter.h"
#include "parser/parser.h"
#include "utils.h"


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

  void Interpreter::set_continuation_marker(Continuation* cont)
  {
    _cont_node_mapping[cont] = _current_expr;
  }

  void Interpreter::activate_contination(Continuation* cont)
  {
    map<Continuation*, parser::nodes::expression_node*>::iterator it = _cont_node_mapping.find(cont);
    if(it != _cont_node_mapping.end()) {
      _current_expr = it->second;
      _current_scope = cont->activation_scope();
    } else {
      error("Invalid Continuation activation: ") << cont->to_s() << std::endl;      
    }
  }
}
