#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include "parser/nodes/expression_list.h"
#include "scope.h"
#include "continuation.h"

namespace fancy {

  class Interpreter : public gc_cleanup
  {
  public:
    Interpreter(parser::nodes::expression_node* expressions, Scope* initial_scope);
    virtual ~Interpreter() {}

    parser::nodes::expression_node* expressions() const { return _expressions; }
    parser::nodes::expression_node* current_expression() const { return _current_expr; }
    Scope* current_scope() const { return _current_scope; }

    void run();

    void set_continuation_marker(Continuation* cont);

    void activate_contination(Continuation* cont);

  private:
    parser::nodes::expression_node* _expressions;
    parser::nodes::expression_node* _current_expr;
    Scope* _current_scope;
    unsigned int _expr_count;
    map<Continuation*, parser::nodes::expression_node*> _cont_node_mapping;
  };

}

#endif /* _INTERPRETER_H_ */
