#include <cassert>
#include "operator_send.h"
#include "../../scope.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      OperatorSend::OperatorSend(Expression* receiver,
                                 Identifier* operator_name,
                                 Expression* operand) :
        _receiver(receiver),
        _operator_name(operator_name),
        _operand(operand)
      {
        assert(receiver);
        assert(operator_name);
        assert(operand);
      }

      OperatorSend::~OperatorSend()
      {
      }

      FancyObject* OperatorSend::eval(Scope *scope, Interpreter* interp)
      {
        // FancyObject* self = scope->current_self();
        FancyObject* args[1] = { _operand->eval(scope, interp) };
        FancyObject* receiver_obj = _receiver->eval(scope, interp);
        return receiver_obj->send_message(_operator_name->name(), args, 1, scope, interp, scope->current_self());
      }

      EXP_TYPE OperatorSend::type() const
      {
        return EXP_OPCALL;
      }

    }
  }
}
