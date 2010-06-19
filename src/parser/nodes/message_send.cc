#include <sstream>

#include "message_send.h"
#include "../../scope.h"
#include "../../bootstrap/core_classes.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      MessageSend::MessageSend(Expression* receiver,
                               send_arg_node *method_args) :
        _receiver(receiver)
      {
        for(send_arg_node *tmp = method_args; tmp != NULL; tmp = tmp->next) {
          _arg_expressions.push_front(pair<Identifier*, Expression*>(tmp->argname, tmp->argexpr));
        }

        init_method_ident();
      }

      MessageSend::MessageSend(Expression* receiver, Identifier* method_ident) :
        _receiver(receiver),
        _method_ident(method_ident)
      {
      }

      MessageSend::~MessageSend()
      {
      }

      FancyObject* MessageSend::eval(Scope *scope, Interpreter* interp)
      {
        int size = _arg_expressions.size();
        FancyObject* *args = new FancyObject*[size];
        int i = 0;
        list< pair<Identifier*, Expression*> >::iterator it;
        for(it = _arg_expressions.begin(); it != _arg_expressions.end() && i < size; it++) {
          args[i] = it->second->eval(scope, interp);
          i++;
        }  
  
        FancyObject* retval = nil;

        // check for super call
        if(_receiver->type() == EXP_SUPER) {
          retval = scope->current_self()->send_super_message(_method_ident->name(), args, size, scope, interp, scope->current_self());
        } else {
          // if no super call, do normal method call
          FancyObject* receiver_obj = _receiver->eval(scope, interp);
          retval = receiver_obj->send_message(_method_ident->name(), args, size, scope, interp, scope->current_self());
        }
        delete[] args;
        return retval;
      }

      EXP_TYPE MessageSend::type() const
      {
        return EXP_METHODCALL;
      }

      void MessageSend::init_method_ident()
      {
        stringstream str;
        list< pair<Identifier*, Expression*> >::iterator it;
        for(it = _arg_expressions.begin(); it != _arg_expressions.end(); it++) {
          str << it->first->name();
          str << ":";
        }

        _method_ident = Identifier::from_string(str.str());
      }

    }
  }
}
