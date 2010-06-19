#ifndef _CLASS_DEFINITION_H_
#define _CLASS_DEFINITION_H_

#include "../../expression.h"
#include "../../array.h"
#include "expression_list.h"
#include "identifier.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      class ClassDefExpr : public Expression
      {
      public:
        ClassDefExpr(Identifier* class_name, ExpressionList* class_body);
        ClassDefExpr(Identifier* superclass_name, Identifier* class_name, ExpressionList* class_body);
        virtual ~ClassDefExpr();

        virtual FancyObject* eval(Scope *scope, Interpreter* interp);
        virtual EXP_TYPE type() const;
  
      private:
        Class* _superclass;
        Identifier* _superclass_name;
        Identifier* _class_name;
        ExpressionList* _class_body;
      };

    }
  }
}

#endif /* _CLASS_DEFINITION_H_ */
