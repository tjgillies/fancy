#include "../fancy_object.h"
#include "../string.h"
#include "../encoding.h"
#include "encoding_utf32.h"
#include "../bootstrap/core_classes.h"

namespace fancy {
  FancyEncodingUTF32::FancyEncodingUTF32() : FancyEncoding(string("UTF-8")) {
  }

  FancyEncoding *FancyEncodingUTF32::clone() const {
    return new FancyEncodingUTF32();
  }

  FancyString *FancyEncodingUTF32::substr(const FancyString *str,int start,int end) const {
    return NULL;
  }

  int FancyEncodingUTF32::strlen(const FancyString *str) const {
    return 0;
  }

  FancyString *FancyEncodingUTF32::characterAt(const FancyString *str,int index) const {
    return 0;
  }

  FancyString *FancyEncodingUTF32::downcase(const FancyString *str) const {
    return NULL;
  }

  FancyString *FancyEncodingUTF32::upcase(const FancyString *str) const {
    return NULL;
  }

}

/* eof */