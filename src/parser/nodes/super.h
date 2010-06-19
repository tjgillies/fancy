#ifndef _PARSER_NODES_SUPER_H_
#define _PARSER_NODES_SUPER_H_

#include "../../expression.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      class Super : public Expression
      {
      public:
        Super();
        virtual ~Super();

        virtual FancyObject* eval(Scope *scope, Interpreter* interp);
        virtual EXP_TYPE type() const;
      };

    }
  }
}

#endif /* _PARSER_NODES_SUPER_H_ */
