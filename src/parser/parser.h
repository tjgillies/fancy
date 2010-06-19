#ifndef _PARSER_PARSER_H_
#define _PARSER_PARSER_H_

#include <list>
#include <stack>
#include <string>

#include "../fancy_object.h"
#include "nodes/expression_list.h"

using namespace std;

struct yy_buffer_state;
extern int yylineno;

/* Size of default input buffer. */
#define YY_BUF_SIZE 16384

namespace fancy {
  namespace parser {

    struct parser_buffer {
      yy_buffer_state* buffstate;
      int lineno;
      string filename;
      FILE *file;
      nodes::expression_node* expression_list;
    };

    extern string current_file;
    extern stack<parser_buffer> parse_buffers;
    extern list<string> load_path;
    extern FancyObject* last_value;
    extern nodes::expression_node* all_exprs;

    void parse_file(string &filename);
    FancyObject* parse_string(const string &code);
    bool push_buffer(const string &filename, nodes::expression_node* curr_expression_list);
    void pop_buffer();

    FILE* find_open_file(const string &filename);
    string dirname_for_path(const string &path);
    string filename_for_path(const string &path);
    bool is_whitespace(const string &str);
  }
}

#endif /* _PARSER_PARSER_H_ */
