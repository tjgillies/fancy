#include "includes.h"

// used for parse_string() in String#eval
#include "../parser/parser.h"

#include "../encodings/encodings.h"

#include "../string.h"
#include "../number.h"
#include "../block.h"

namespace fancy {
  namespace bootstrap {

    void init_string_class()
    {
      DEF_CLASSMETHOD(StringClass,
                      "new",
                      "String constructor.",
                      new);

      DEF_METHOD(StringClass,
                  "encoding",
                  "Returns the encoding of the string.",
                  encoding);

      DEF_METHOD(StringClass,
                 "downcase",
                 "Returns the downcased version of self.",
                 downcase);

      DEF_METHOD(StringClass,
                 "upcase",
                 "Returns the upcased version of self.",
                 upcase);

      DEF_METHOD(StringClass,
                 "from:to:",
                 "Returns a substring of self starting at index from: till to:.",
                 from__to);

      DEF_METHOD(StringClass,
                 "==",
                 "String comparison.",
                 eq);

      DEF_METHOD(StringClass,
                 "+",
                 "String concatenation.",
                 plus);

      DEF_METHOD(StringClass,
                 "each:",
                 "Calls the given Block with each character in self",
                 each);

      DEF_METHOD(StringClass,
                 "each_byte:",
                 "Calls the given Block with each byte in self",
                 each_byte);

      DEF_METHOD(StringClass,
                 "at:",
                 "Returns the character at the given index.",
                 at);

      DEF_METHOD(StringClass,
                 "eval",
                 "Interprets the String as Fancy code and tries to run it.",
                 eval);
    }

    /**
     * String class methods
     */
    CLASSMETHOD(StringClass, new)
    {
      return FancyString::from_value("");
    }

    /**
     * String instance methods
     */

    METHOD(StringClass, encoding)
    {
      FancyString *str = dynamic_cast<FancyString*>(self);
      return (FancyObject *)str->encoding();
    }

    METHOD(StringClass, downcase)
    {
      FancyString* str = dynamic_cast<FancyString*>(self);
      FancyString* nstr = str->encoding()->downcase(str);
      return nstr;
    }

    METHOD(StringClass, upcase)
    {
      FancyString* str = dynamic_cast<FancyString*>(self);
      FancyString* nstr = str->encoding()->upcase(str);
      return nstr;
    }

    METHOD(StringClass, from__to)
    {
      EXPECT_ARGS("String#from:to:", 2);
      FancyString *str = dynamic_cast<FancyString*>(self);
      FancyObject* arg1 = args[0];
      FancyObject* arg2 = args[1];
  
      if(IS_INT(arg1) && IS_INT(arg2)) {
        Number* idx1 = dynamic_cast<Number*>(arg1);
        Number* idx2 = dynamic_cast<Number*>(arg2);
        FancyString *substr;

        // deal with negative indexes
        if(idx2->intval() < 0) {
          substr = str->encoding()->substr(str,idx1->intval(), (str->encoding()->strlen(str) + 1) + idx2->intval());
        } else {
          substr = str->encoding()->substr(str,idx1->intval(), (idx2->intval() + 1) - idx1->intval());
        }
        return substr;
      } else {
        errorln("String#to:from: expects 2 Integer arguments");
        return self;
      }

      return nil;
    }

    METHOD(StringClass, eq)
    {
      EXPECT_ARGS("String#eq:", 1);
      FancyObject* arg = args[0];
      if(IS_STRING(arg)) {
        const unsigned char *str1 = dynamic_cast<FancyString*>(self)->value();
        const unsigned char *str2 = dynamic_cast<FancyString*>(arg)->value();
        if(strcmp((const char *)str1,(const char *)str2) == 0) {
          return t;
        }
      }
      return nil;
    }

    METHOD(StringClass, plus)
    {
      EXPECT_ARGS("String#+", 1);
      if(FancyString* arg = dynamic_cast<FancyString*>(args[0])) {
        const unsigned char *str1 = dynamic_cast<FancyString*>(self)->value();
        const unsigned char *str2 = arg->value();
        return FancyString::from_value(string((const char *)str1) + string((const char *)str2));
      }
      errorln("String#+ expects String argument.");
      return nil;
    }

    METHOD(StringClass, each)
    {
      EXPECT_ARGS("String#each:", 1);
      if(Block* block = dynamic_cast<Block*>(args[0])) {
        FancyString *str = dynamic_cast<FancyString*>(self);
        size_t len = str->encoding()->strlen(str);

        FancyObject* retval = nil;
        for(size_t i=0;i<len;++i) {
          FancyString *chr = str->encoding()->characterAt(str,i);
          FancyObject* block_args[1] = { chr };
          retval = block->call(self, block_args, 1, scope);
        }
        return retval;
      }
      errorln("String#each: expects Block argument.");
      return nil;
    }

    METHOD(StringClass, each_byte)
    {
      EXPECT_ARGS("String#each_byte:", 1);
      if(Block* block = dynamic_cast<Block*>(args[0])) {
        FancyString *str = dynamic_cast<FancyString*>(self);
        size_t len = str->bytes();
        const unsigned char *c = str->value();

        FancyObject* retval = nil;
        for(size_t i=0;i<len;++i) {
          FancyObject* block_args[1] = { new Number((int)c[i]) };
          retval = block->call(self, block_args, 1, scope);
        }
        return retval;
      }
      errorln("String#each: expects Block argument.");
      return nil;
    }

    METHOD(StringClass, at)
    {
      EXPECT_ARGS("String#at:", 1);
      if(Number* index = dynamic_cast<Number*>(args[0])) {
        FancyString* str = dynamic_cast<FancyString*>(self);
        return str->encoding()->characterAt(str,index->intval());
      }
      errorln("String#at: expects Number argument.");
      return nil;
    }

    METHOD(StringClass, eval)
    {
      string code = string((const char *)(self->to_s().value()));
      return parser::parse_string(code);
    }

  }
}
