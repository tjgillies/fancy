#include "block.h"
#include "string.h"
#include "symbol.h"
#include "bootstrap/core_classes.h"

namespace fancy {

  Block::Block(ExpressionList* body, Scope *creation_scope) :
    FancyObject(BlockClass),
    _body(body),
    _creation_scope(creation_scope),
    _override_self(false),
    _argcount(0)
  {
    _docstring = "<BLOCK>";
    init_orig_block_arg_values();
  }

  Block::Block(list<parser::nodes::Identifier*> argnames, ExpressionList* body, Scope *creation_scope) :
    FancyObject(BlockClass),
    _argnames(argnames),
    _body(body),
    _creation_scope(creation_scope),
    _override_self(false)
  {
    _docstring = "<BLOCK>";
    _argcount = argnames.size();
    init_orig_block_arg_values();
  }

  Block::~Block()
  {
  }

  EXP_TYPE Block::type() const
  {
    return EXP_BLOCK;
  }

  const FancyString Block::to_s() const
  {
    return FancyString("<Block>");
  }

  FancyObject* Block::call(FancyObject* self, FancyObject* *args, int argc, Scope *scope)
  {
    // check if block is empty
    if(_body->size() == 0)
      return nil;

    if(argc > 0) {
      list<parser::nodes::Identifier*>::iterator name_it = _argnames.begin();
      int i = 0;
      while(name_it != _argnames.end() && i < argc) {
        string name = (*name_it)->name();
        // set new value (argument)
        _creation_scope->define(name, args[i]);
        name_it++;
        i++;
      }
    }

    FancyObject* return_value = call(self, scope);

    // reset old values for param names in creation_scope (if any args given)
    if(argc > 0) {
      list<parser::nodes::Identifier*>::iterator name_it = _argnames.begin();
      list<FancyObject*>::iterator val_it = _block_arg_orig_values.begin();
      while(name_it != _argnames.end() && val_it != _block_arg_orig_values.end()) {
        string name = (*name_it)->name();
        _creation_scope->define(name, (*val_it));
        name_it++;
        val_it++;
      }
    }

    return return_value;
  }

  FancyObject* Block::call(FancyObject* self, Scope *scope)
  {
    // check if block is empty
    if(_body->size() == 0) {
      return nil;
    }

    FancyObject* old_self = _creation_scope->current_self();
    if(_override_self) {
      _creation_scope->set_current_self(self);
    }

    // finally, eval the blocks body expression
    FancyObject* return_value = _body->eval(_creation_scope);

    // restore old self if _override_self
    if(_override_self) {
      _creation_scope->set_current_self(old_self);
    }
  
    return return_value;
  }

  void Block::set_creation_scope(Scope *creation_scope)
  {
    _creation_scope = creation_scope;
  }

  Scope* Block::creation_scope() const
  {
    return _creation_scope;
  }

  vector<FancyObject*> Block::args()
  {
    vector<FancyObject*> args(_argnames.size(), nil);
    int i = 0;
    for(list<parser::nodes::Identifier*>::iterator it = _argnames.begin();
        it != _argnames.end();
        it++) {
      args[i] = Symbol::from_string(":" + (*it)->name());
      i++;
    }
    return args;
  }

  unsigned int Block::argcount() const
  {
    return _argcount;
  }

  void Block::override_self(bool do_it)
  {
    _override_self = do_it;
  }

  bool Block::is_empty() const
  {
    return _body->size() == 0;
  }

  void Block::init_orig_block_arg_values()
  {
    if(_argnames.size() > 0) {
      list<parser::nodes::Identifier*>::iterator name_it = _argnames.begin();
      while(name_it != _argnames.end()) {
        // save old value for name in _block_arg_orig_values;
        _block_arg_orig_values.push_back(_creation_scope->get((*name_it)->name()));
        name_it++;
      }
    }
  }
}
