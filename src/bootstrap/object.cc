#include "includes.h"

#include "../array.h"
#include "../block.h"
#include "../string.h"
#include "../number.h"


namespace fancy {
  namespace bootstrap {

    void init_object_class()
    {
      /**
       * Object class methods
       */
      DEF_CLASSMETHOD(ObjectClass,
                      "new",
                      "New method for creating new instances of classes.\
It is expected, that self (the receiver) is a class object.",
                      new);

      DEF_CLASSMETHOD(ObjectClass,
                      "new:",
                      "Same as Object##new, but also expecting arguments\
and passing them on to the initialize: method of the class.",
                      new_with_arg);

      /**
       * Object instance methods
       */
      DEF_METHOD(ObjectClass,
                 "and:",
                 "Boolean conjunction.",
                 and);

      DEF_METHOD(ObjectClass,
                 "or:",
                 "Boolean disjunction.",
                 or);

      DEF_METHOD(ObjectClass,
                 "not",
                 "Boolean negation. In Fancy, everything non-nil is logically true.",
                 not);

      DEF_METHOD(ObjectClass,
                 "to_s",
                 "Returns string representation of object.",
                 to_s);

      DEF_METHOD(ObjectClass,
                 "inspect",
                 "Returns detailed string representation of object.",
                 inspect);
  
      DEF_METHOD(ObjectClass,
                 "_class",
                 "Returns the class of the object.",
                 class);  

      DEF_METHOD(ObjectClass,
                 "define_singleton_method:with:",
                 "Defines singleton method on object.",
                 define_singleton_method__with);

      DEF_METHOD(ObjectClass,
                 "==",
                 "Índicates, if two objects are equal.",
                 eq);
  
      // DEF_METHOD(ObjectClass,
      //            "is_a?:",
      //            "Indicates, if an object is an instance of a given Class.",
      //            is_a);

      DEF_METHOD(ObjectClass,
                 "send:",
                 "Sends a message to an object with no arguments.",
                 send);

      DEF_METHOD(ObjectClass,
                 "send:params:",
                 "Sends a message to an object with an Array of arguments.",
                 send__params);
  
      DEF_METHOD(ObjectClass,
                 "responds_to?:",
                 "Indicates, if an object responds to a given method name.",
                 responds_to);

      DEF_METHOD(ObjectClass,
                 "get_slot:",
                 "Returns the value of slot.",
                 get_slot);

      DEF_METHOD(ObjectClass,
                 "set_slot:value:",
                 "Sets the value of slot.",
                 set_slot__value);
  
      DEF_METHOD(ObjectClass,
                 "docstring:",
                 "Sets the docstring for an object.",
                 docstring_set);

      DEF_METHOD(ObjectClass,
                 "docstring",
                 "Returns the docstring for an object.",
                 docstring_get);

      DEF_METHOD(ObjectClass,
                 "methods",
                 "Returns all methods of an object in an Array.",
                 methods);

      DEF_METHOD(ObjectClass,
                 "%M",
                 "Returns the metadata attached to this object.",
                 metadata);

      DEF_METHOD(ObjectClass,
                 "%M:",
                 "Sets the metadata for this object.",
                 set_metadata);

      DEF_METHOD(ObjectClass,
                 "memaddr",
                 "Returns the raw memory pointer adress as a Number",
                 memaddr);
    }

    /**
     * Object class methods
     */

    CLASSMETHOD(ObjectClass, new)
    {
      if(IS_CLASS(self)) {
        // deal with special case of Class class for dynamically
        // creating Class Objects
        if(self == ClassClass) {
          return new Class(ObjectClass);
        } else {
          // this deals with the "normal" Classes that create "normal"
          // Objects
          Class* the_class = dynamic_cast<Class*>(self);
          FancyObject* new_instance = the_class->create_instance();
          if(new_instance->responds_to("initialize")) {
            new_instance->send_message("initialize", args, argc, scope, self);
          }
          return new_instance;
        }
      } else {
        errorln("Expected instance to be a class. Not the case!");
      }
      return nil;
    }

    CLASSMETHOD(ObjectClass, new_with_arg)
    {
      EXPECT_ARGS("Object##new:", 1);
      if(IS_CLASS(self)) {
        // same as above, check for Class class special case
        if(self == ClassClass) {
          if(Class* superclass = dynamic_cast<Class*>(args[0])) {
            return new Class(superclass);
          } else {
            errorln("Expected Class argument as Superclass.");
            return nil;
          }
        } else {
          Class* the_class = dynamic_cast<Class*>(self);
          FancyObject* new_instance = the_class->create_instance();
          if(new_instance->responds_to("initialize:")) {
            new_instance->send_message("initialize:", args, argc, scope, self);
          }
          return new_instance;
        }
      } else {
        errorln("Expected instance to be a class. Not the case!");
      }
      return nil;
    }

    /**
     * Object instance methods
     */

    METHOD(ObjectClass, and)
    {
      EXPECT_ARGS("Object#and:", 1);
      if(self != nil && args[0] != nil) {
        return t;
      } else {
        return nil;
      }
    }

    METHOD(ObjectClass, or)
    {
      EXPECT_ARGS("Object#or:", 1);
      if(self != nil || args[0] != nil) {
        return t;
      } else {
        return nil;
      }
    }

    METHOD(ObjectClass, not)
    {
      if(self == nil) {
        return t;
      } else {
        return nil;
      }
    }

    METHOD(ObjectClass, to_s)
    {
      return FancyString::from_value(self->to_s().value());
    }

    METHOD(ObjectClass, inspect)
    {
      return FancyString::from_value(string((const char *)(self->inspect().value())) + " : " + self->get_class()->name());
    }

    METHOD(ObjectClass, class)
    {
      return self->get_class();
    }

    METHOD(ObjectClass, define_singleton_method__with)
    {
      EXPECT_ARGS("Object#define_singleton_method:with:", 2);
      FancyObject* arg1 = args[0];
      FancyObject* arg2 = args[1];

      if(IS_STRING(arg1) && IS_BLOCK(arg2)) {
        self->def_singleton_method(string((const char *)(dynamic_cast<FancyString*>(arg1)->value())), dynamic_cast<Block*>(arg2));
        return t;
      } else {
        errorln("Object#define_singleton_method:with: expects String and Block arguments.");
        return nil;
      }
    }

    METHOD(ObjectClass, eq)
    {
      EXPECT_ARGS("Object#==", 1);
      if(self == args[0]) { // this is kind of obvious ;)
        return t;
      } else {
        return self->equal(args[0]);
      }
    }

    // METHOD(ObjectClass, is_a)
    // {
    //   EXPECT_ARGS("Object#is_a?:", 1);
    //   Class* the_class = dynamic_cast<Class*>(args[0]);
    //   if(the_class) {
    //     if(self->get_class()->subclass_of(the_class))
    //       return t;
    //   } else {
    //     errorln("Object#is_a?: expects Class argument.");
    //   }
    //   return nil;
    // }

    METHOD(ObjectClass, send)
    {
      EXPECT_ARGS("Object#send:", 1);
      string method_name = (const char *)(args[0]->to_s().value());
      return self->send_message(method_name, 0, 0, scope, self);
    }

    METHOD(ObjectClass, send__params)
    {
      EXPECT_ARGS("Object#send:params:", 2);
      string method_name = (const char *)(args[0]->to_s().value());
      if(Array* arr = dynamic_cast<Array*>(args[1])) {
        int size = arr->size();
        FancyObject* *arg_array = new FancyObject*[size];
        for(int i = 0; i < size; i++) {
          arg_array[i] = arr->at(i);
        }
        FancyObject* retval = self->send_message(method_name, arg_array, size, scope, self);
        delete[] arg_array; // cleanup
        return retval;
      } else {
        errorln("Object#send:params: expects Array as second argument.");
      }
      return nil;
    }

    METHOD(ObjectClass, responds_to)
    {
      EXPECT_ARGS("Object#responds_to?:", 1);
      string method_name = (const char *)(args[0]->to_s().value());
      if(self->responds_to(method_name)) {
        return t;
      }
      return nil;
    }

    METHOD(ObjectClass, get_slot)
    {
      EXPECT_ARGS("Object#get_slot:", 1);
      string slot_name = "@" + string((const char *)(args[0]->to_s().value()));
      FancyObject* slot = self->get_slot(slot_name);
      return slot;
    }

    METHOD(ObjectClass, set_slot__value)
    {
      EXPECT_ARGS("Object#set_slot:value:", 2);
      string slot_name = "@" + string((const char *)(args[0]->to_s().value()));
      FancyObject* value = args[1];
      self->set_slot(slot_name, value);
      return self;
    }

    METHOD(ObjectClass, docstring_set)
    {
      EXPECT_ARGS("Object#docstring:", 1);
      self->set_docstring(string((const char *)(args[0]->to_s().value())));
      return t;
    }

    METHOD(ObjectClass, docstring_get)
    {
      return FancyString::from_value(self->docstring());
    }

    METHOD(ObjectClass, methods)
    {
      return self->methods();
    }

    METHOD(ObjectClass, metadata)
    {
      return self->metadata();
    }

    METHOD(ObjectClass, set_metadata)
    {
      EXPECT_ARGS("Object#%M:", 1);
      self->set_metadata(args[0]);
      return self;
    }

    METHOD(ObjectClass, memaddr)
    {
      return Number::from_int((long)self);
    }

  }
}
