#include "../fancy_object.h"
#include "../string.h"
#include "../encoding.h"
#include "encoding_utf8.h"
#include "../bootstrap/core_classes.h"

#include <unicode/unistr.h>

namespace fancy {
  using namespace icu;

  FancyEncodingUTF8::FancyEncodingUTF8() : FancyEncoding(string("UTF-8")) {
  }

  FancyEncoding *FancyEncodingUTF8::clone() const
  {
    return new FancyEncodingUTF8();
  }

  FancyString *FancyEncodingUTF8::substr(const FancyString *str,int start,int end) const {
    UnicodeString str1 = UnicodeString::fromUTF8((const char *)(str->value()));
    UnicodeString substr(str1,(int32_t)start,(int32_t)(end-start));

    string utf8str;
    StringByteSink<string> sbs(&utf8str);

    substr.toUTF8(sbs);

    return new FancyString(utf8str.c_str());
  }

  int FancyEncodingUTF8::strlen(const FancyString *str) const {
    UnicodeString str1 = UnicodeString::fromUTF8((const char *)(str->value()));
    return str1.countChar32();
  }

  FancyString *FancyEncodingUTF8::characterAt(const FancyString *str,int index) const {
    UnicodeString str1 = UnicodeString::fromUTF8((const char *)(str->value()));
    string utf8str;
    StringByteSink<string> sbs(&utf8str);

    UChar chr = str1[index];

    if(chr == 0xFFFF) return NULL;
    str1 = chr;
    str1.toUTF8(sbs);

    return new FancyString(utf8str.c_str());
  }

  FancyString *FancyEncodingUTF8::downcase(const FancyString *str) const {
    UnicodeString str1 = UnicodeString::fromUTF8((const char *)(str->value())).toLower();
    string utf8str;
    StringByteSink<string> sbs(&utf8str);

    str1.toUTF8(sbs);

    return new FancyString(utf8str.c_str());
  }

  FancyString *FancyEncodingUTF8::upcase(const FancyString *str) const {
    UnicodeString str1 = UnicodeString::fromUTF8((const char *)(str->value())).toUpper();
    string utf8str;
    StringByteSink<string> sbs(&utf8str);

    str1.toUTF8(sbs);

    return new FancyString(utf8str.c_str());
  }

}

/* eof */