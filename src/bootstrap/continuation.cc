#include "includes.h"

#include "../array.h"
#include "../block.h"
#include "../continuation.h"

namespace fancy {
  namespace bootstrap {

    void init_continuation_class()
    {
      DEF_METHOD(ContinuationClass,
                 "call",
                 "Calls (resumes) the Continuation with no arguments.",
                 call);

      DEF_METHOD(ContinuationClass,
                 "call:",
                 "Calls (resumes) the Continuation with the given arguments (single value or Array).",
                 call_with_arg);
    }

    METHOD(ContinuationClass, call)
    {
      Continuation* cont = dynamic_cast<Continuation*>(self);
      return cont->call(self, scope, interp);
    }

    METHOD(ContinuationClass, call_with_arg)
    {
      EXPECT_ARGS("Continuation#call:", 1);
      Continuation* cont = dynamic_cast<Continuation*>(self);
      FancyObject* first_arg = args[0];
      if(Array* args_array = dynamic_cast<Array*>(first_arg)) {
        int size = args_array->size();
        FancyObject* *args_array_arr = new FancyObject*[size];
        for(int i = 0; i < size; i++) {
          args_array_arr[i] = args_array->at(i);
        }
        FancyObject* retval =  cont->call(self, args_array_arr, size, scope, interp);
        delete[] args_array_arr; // cleanup  before leave
        return retval;
      } else {
        FancyObject* call_args[1] = { first_arg };
        return cont->call(self, call_args, 1, scope, interp);
      }
    }

  }
}
 
