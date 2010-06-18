#include "../fancy_object.h"
#include "../string.h"
#include "../encoding.h"
#include "encoding_utf16.h"
#include "../bootstrap/core_classes.h"

namespace fancy {
  FancyEncodingUTF16::FancyEncodingUTF16() : FancyEncoding(string("UTF-8")) {
  }

  FancyEncoding *FancyEncodingUTF16::clone() const
  {
    return new FancyEncodingUTF16();
  }

  FancyString *FancyEncodingUTF16::substr(const FancyString *str,int start,int end) const {
    return NULL;
  }

  int FancyEncodingUTF16::strlen(const FancyString *str) const {
    return 0;
  }

  FancyString *FancyEncodingUTF16::characterAt(const FancyString *str,int index) const {
    return 0;
  }

  FancyString *FancyEncodingUTF16::downcase(const FancyString *str) const {
    return NULL;
  }

  FancyString *FancyEncodingUTF16::upcase(const FancyString *str) const {
    return NULL;
  }

}

/* eof */