#include "number.h"
#include "encodings/encodings.h"
#include "string.h"
#include "bootstrap/core_classes.h"

#include <iostream>
#include <cstdlib>
#include <cstring>

namespace fancy {

  static string __fake_newline = "\\n";
  static string __fake_tab = "\\t";
  static string __newline = "\n";
  static string __tab =  "\t";

  unsigned char *FancyString::normalize(const unsigned char *chr,size_t *bytes) {
    static const char *strings[] = {"\\n","\\t",NULL};
    static const char *replacements = "\n\t";

    size_t len = ::strlen((const char *)chr),i,replaced;
    unsigned char *new_str = (unsigned char *)malloc(2 * len),*ptr,*ptr1;

    *bytes = 0;

    for(ptr=(unsigned char *)chr,ptr1=new_str;*ptr;++ptr) {
      replaced = 0;
      for(i=0;strings[i];++i) {
        if(strncmp((const char *)ptr,strings[i],::strlen(strings[i])) == 0) {
          *ptr1++ = replacements[i];
          ptr += ::strlen(strings[i]);
          replaced = 1;
          (*bytes)++;
          break;
        }
      }

      if(!replaced) {
        *ptr1++ = *ptr;
        (*bytes)++;
      }
    }

    *ptr1 = 0;
    return new_str;
  }

  FancyString::FancyString(const string &value) :
    FancyObject(StringClass)
  {
    _value = FancyString::normalize((const unsigned char *)value.c_str(),&_bytes);
    _encoding = new FancyEncodingUTF8();
  }

  FancyString::FancyString(const unsigned char *value) :
    FancyObject(StringClass)
  {
    _value = FancyString::normalize(value,&_bytes);
    _encoding = new FancyEncodingUTF8();
  }

  FancyString::FancyString(const unsigned char value) :
    FancyObject(StringClass)
  {
    unsigned char chr[2];

    chr[0] = value;
    chr[1] = 0;

    _value = FancyString::normalize(chr,&_bytes);
    _encoding = new FancyEncodingUTF8();
  }

  FancyString::FancyString(const FancyString &str) : FancyObject(StringClass) {
    _bytes = str._bytes;
    _value = (unsigned char *)malloc(_bytes+1);
    memcpy(_value,str.value(),_bytes+1);
    _encoding = ((FancyEncoding *)str.encoding())->clone();
  }

  size_t FancyString::bytes() const
  {
    return _bytes;
  }

  const FancyEncoding *FancyString::encoding() const
  {
    return _encoding;
  }


  FancyString *FancyString::substr(int start,int end) const { return _encoding->substr(this,start,end); }
  int FancyString::strlen() const { return _encoding->strlen(this); }
  FancyString *FancyString::characterAt(int index) const { return _encoding->characterAt(this,index); }
  Number *FancyString::codePointAt(int index) const { return _encoding->codePointAt(this,index); }
  FancyString *FancyString::downcase() const { return _encoding->downcase(this); }
  FancyString *FancyString::upcase() const { return _encoding->upcase(this); }


  FancyString::~FancyString()
  {
    free(_value);
    delete _encoding;
  }

  FancyObject* FancyString::equal(FancyObject* other) const
  {
    if(!IS_STRING(other))
      return nil;

    FancyString* other_string = (FancyString*)other;
    if(strcmp((const char *)_value,(const char *)other_string->_value) == 0)
      return t;
    return nil;
  }

  EXP_TYPE FancyString::type() const
  {
    return EXP_STRING;
  }

  const FancyString FancyString::to_s() const
  {
    return *this;
  }

  const FancyString FancyString::inspect() const
  {
    return FancyString("\"" + string((const char *)_value) + "\"");
  }

  const unsigned char *FancyString::value() const
  {
    return _value;
  }

  //map<string, FancyString*> FancyString::value_cache;
  FancyString* FancyString::from_value(const string &value)
  {
    //TODO: check for the cache!
    /*if(value_cache.find(value) != value_cache.end()) {
      return value_cache[value];
    } else {*/
      // insert new value into value_cache & return new number value
      FancyString* new_string = new FancyString(value);
      //value_cache[value] = new_string;
      return new_string;
    //}
  }
  FancyString* FancyString::from_value(const unsigned char* value)
  {
    //TODO: check for the cache!
    /*if(value_cache.find(value) != value_cache.end()) {
      return value_cache[value];
    } else {*/
      // insert new value into value_cache & return new number value
      FancyString* new_string = new FancyString(value);
      //value_cache[value] = new_string;
      return new_string;
    //}
  }



}
