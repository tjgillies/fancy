#include "includes.h"

#include "../string.h"
#include "../encoding.h"

namespace fancy {
  namespace bootstrap {
    void init_encoding_class()
    {
      DEF_METHOD(EncodingClass,
                 "name",
                 "Returns the encoding name, e.g. UTF-8 for UTF-8 encoded strings.",
                 name);
    }

    METHOD(EncodingClass, name)
    {
      string n = dynamic_cast<FancyEncoding*>(self)->name();
      return FancyString::from_value(n.c_str());
    }
  }
}

/* eof */