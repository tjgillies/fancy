#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "../vendor/gc/include/gc.h"
#include "../vendor/gc/include/gc_cpp.h"
#include "../vendor/gc/include/gc_allocator.h"

namespace fancy {

  class Scope;
  class FancyObject;
  class Interpreter;

  /**
   * Enum holding all possible types of objects/expressions in Fancy.
   */
  enum EXP_TYPE {
    EXP_NIL = 0,
    EXP_TRUE,
    EXP_INTEGER,
    EXP_DOUBLE,
    EXP_IDENTIFIER,
    EXP_SYMBOL,
    EXP_STRING,
    EXP_HASH,
    EXP_HASHLITERAL,
    EXP_REGEX,
    EXP_ARRAY,
    EXP_ARRAYLITERAL,
    EXP_METHOD,
    EXP_NATIVEMETHOD,
    EXP_METHODCALL,
    EXP_OPCALL,
    EXP_ASSIGNEXPR,
    EXP_RETURNSTATEMENT,
    EXP_REQUIRESTATEMENT,
    EXP_EXPRLIST,
    EXP_METHODDEFEXPR,
    EXP_OPERATORDEFEXPR,
    EXP_MODULE,
    EXP_CLASS,
    EXP_CLASSINSTANCE,
    EXP_CLASSDEFEXPR,
    EXP_BLOCK,
    EXP_BLOCKLITERAL,
    EXP_FILE,
    EXP_DIRECTORY,
    EXP_SCOPE,
    EXP_EXCEPTION,
    EXP_TRYCATCHBLOCK,
    EXP_SUPER
  };

  /**
   * Interface for everything that can evaluate into a FancyObject
   * instance.  
   * This includes parser nodes (see src/parser/nodes/) as * well as
   * FancyObjects (they evaluate to themself)
   */
  class Expression : public gc_cleanup
  {
  public:
    virtual FancyObject* eval(Scope *scope, Interpreter* interp) = 0;
    virtual EXP_TYPE type() const = 0;
  };

}

#endif /* _EXPRESSION_H_ */
