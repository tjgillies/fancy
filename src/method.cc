#include <sstream>

#include "string.h"
#include "method.h"
#include "utils.h"
#include "bootstrap/core_classes.h"

namespace fancy {

  Method::Method(Identifier* op_name, Identifier* op_argname, ExpressionList* body) :
    FancyObject(MethodClass),
    _body(body),
    _is_operator(true)
  {
    _argnames.push_back(pair<Identifier*, Identifier*>(op_name, op_argname));
    init_method_ident();
    init_docstring();
  }

  Method::Method(const list< pair<Identifier*, Identifier*> > argnames,
                 ExpressionList* body) : 
    FancyObject(MethodClass),
    _argnames(argnames),
    _body(body),
    _is_operator(false)
  {
    init_method_ident();
    init_docstring();
  }

  Method::Method() :
    FancyObject(MethodClass),
    _is_operator(false)
  {
  }

  Method::~Method()
  {
  }

  unsigned int Method::argcount() const
  {
    return _argnames.size();
  }

  list< pair<Identifier*, Identifier*> > Method::argnames() const
  {
    return _argnames;
  }

  FancyObject* Method::call(FancyObject* self, FancyObject* *args, int argc, Scope *scope)
  {
    // check if method is empty
    if(_body->size() == 0)
      return nil;

    Scope* call_scope = new Scope(self, scope);

    // check amount of given arguments
    if(_argnames.size() != (unsigned int)argc) {
      error("Given amount of arguments (")
        << argc
        << ") doesn't match expected amount ("
        << _argnames.size()
        << ")";
    } else {
      // if amount ok, set the parameters to the given arguments
      list< pair<Identifier*, Identifier*> >::iterator name_it = _argnames.begin();
      // list<FancyObject*>::iterator arg_it = args.begin();
      int i = 0;
    
      while(name_it != _argnames.end() && i < argc) {
        // name_it->second holds the name of the actual param name 
        // (the first is part of the method name)
        call_scope->define(name_it->second->name(), args[i]);
        name_it++;
        i++;
      }
    
      // finally, eval the methods body expression
      FancyObject* val = _body->eval(call_scope);
      if(!call_scope->is_closed()) {
        delete call_scope;
        call_scope = NULL;
      }
      return val;
    }
  
    return nil;
  }

  FancyObject* Method::call(FancyObject* self, Scope *scope)
  {
    // check if method is empty
    if(_body->size() == 0)
      return nil;

    Scope* call_scope = new Scope(self, scope);
    FancyObject* val = _body->eval(call_scope);
    if(!call_scope->is_closed()) {
      delete call_scope;
      call_scope = NULL;
    }
    return val;
  }

  EXP_TYPE Method::type() const
  {
    return EXP_METHOD;
  }

  const FancyString Method::to_s() const
  {
    return FancyString("<Method : '" + _method_ident + "' Doc:'" + _docstring + "'>");
  }

  void Method::init_method_ident()
  {
    stringstream str;
    list< pair<Identifier*, Identifier*> >::iterator it;
    for(it = _argnames.begin(); it != _argnames.end(); it++) {
      str << it->first->name();
      if(!_is_operator) {
        str << ":";
      }
    }
    _method_ident = str.str();
  }


  void Method::init_docstring()
  {
    _docstring = _body->docstring();
  }

  string Method::name() const
  {
    return _method_ident;
  }

  void Method::set_name(const string &method_name)
  {
    _method_ident = method_name;
  }

}
