#ifndef _OPERATOR_DEFINITION_H_
#define _OPERATOR_DEFINITION_H_

#include "../../expression.h"
#include "../../method.h"
#include "identifier.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      class OperatorDefExpr : public Expression
      {
      public:
        OperatorDefExpr(Identifier* op_name, Method* method);
        virtual ~OperatorDefExpr() {}

        virtual EXP_TYPE type() const;
        virtual FancyObject* eval(Scope *scope, Interpreter* interp);
 
      protected:
        Identifier* _op_name;
        Method* _method;
      };

      class PrivateOperatorDefExpr : public OperatorDefExpr
      {
      public:
        PrivateOperatorDefExpr(Identifier* op_name, Method* method);
        virtual ~PrivateOperatorDefExpr() {}

        virtual FancyObject* eval(Scope *scope, Interpreter* interp);
      };

      class ProtectedOperatorDefExpr : public OperatorDefExpr
      {
      public:
        ProtectedOperatorDefExpr(Identifier* op_name, Method* method);
        virtual ~ProtectedOperatorDefExpr() {}

        virtual FancyObject* eval(Scope *scope, Interpreter* interp);
      };
    }
  }
}

#endif /* _OPERATOR_DEFINITION_H_ */
