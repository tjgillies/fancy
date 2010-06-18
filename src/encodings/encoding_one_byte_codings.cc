#include "../fancy_object.h"
#include "../string.h"
#include "../encoding.h"
#include "encoding_one_byte_codings.h"
#include "../bootstrap/core_classes.h"

namespace fancy {
  FancyEncodingOneByte::FancyEncodingOneByte() : FancyEncoding(string("one-byte")) {
  }

  FancyEncoding *FancyEncodingOneByte::clone() const
  {
    return new FancyEncodingOneByte();
  }

  FancyString *FancyEncodingOneByte::substr(const FancyString *str,int start,int end) const {
    return NULL;
  }

  int FancyEncodingOneByte::strlen(const FancyString *str) const {
    return (int)((FancyString*)(str))->bytes();
  }

  FancyString *FancyEncodingOneByte::characterAt(const FancyString *str,int index) const {
    const unsigned char *val = str->value();
    FancyString *str1 = new FancyString(val[index]);
    return str1;
  }

  FancyString *FancyEncodingOneByte::downcase(const FancyString *str) const {
    unsigned char *ptr,*ptr1;
    unsigned char *buffer = (unsigned char *)malloc(str->bytes()+1);
    FancyString *nstr;

    for(ptr=(unsigned char *)str->value();*ptr;++ptr) *ptr1++ = tolower(*ptr);
    buffer[str->bytes()] = 0;

    nstr = new FancyString(buffer);

    free(buffer);
    return nstr;
  }

  FancyString *FancyEncodingOneByte::upcase(const FancyString *str) const {
    unsigned char *ptr,*ptr1;
    unsigned char *buffer = (unsigned char *)malloc(str->bytes()+1);
    FancyString *nstr;

    for(ptr=(unsigned char *)str->value();*ptr;++ptr) *ptr1++ = toupper(*ptr);
    buffer[str->bytes()] = 0;

    nstr = new FancyString(buffer);

    free(buffer);
    return nstr;
  }
}

/* eof */