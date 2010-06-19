#include "hash_literal.h"
#include "../../hash.h"

namespace fancy {
  namespace parser {
    namespace nodes {

      HashLiteral::HashLiteral(key_val_node *key_val_list)
      {
        for(key_val_node *tmp = key_val_list; tmp != NULL; tmp = tmp->next) {
          _key_val_list.push_back(pair<Expression*, Expression*>(tmp->key, tmp->val));
        }
      }

      HashLiteral::~HashLiteral()
      {
      }

      FancyObject* HashLiteral::eval(Scope *scope, Interpreter* interp)
      {
        map<FancyObject*, FancyObject*> mappings;
        list< pair<Expression*, Expression*> >::iterator it;
        for(it = _key_val_list.begin(); it != _key_val_list.end(); it++) {
          mappings[it->first->eval(scope, interp)] = it->second->eval(scope, interp);
        }
        return new Hash(mappings);
      }

      EXP_TYPE HashLiteral::type() const
      {
        return EXP_HASHLITERAL;
      }

    }
  }
}
