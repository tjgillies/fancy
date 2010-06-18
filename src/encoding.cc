#include "string.h"
#include "encoding.h"
#include "bootstrap/core_classes.h"

namespace fancy {
  FancyEncoding::FancyEncoding(const string encoding) :
    FancyObject(EncodingClass)
  {
    _enc_name = encoding;
  }
  FancyEncoding::~FancyEncoding()
  {
  }

  FancyEncoding *FancyEncoding::clone() const
  {
    return NULL;
  }

  FancyObject* FancyEncoding::equal(const FancyObject* other)
  {
    if(other->type() != this->type())
      return nil;

    FancyEncoding* other_enc = (FancyEncoding*)other;
    if(_enc_name == other_enc->_enc_name)
      return t;

    return nil;
  }

  EXP_TYPE FancyEncoding::type() const
  {
    return EXP_ENCODING;
  }

  const FancyString FancyEncoding::to_s() const
  {
    return FancyString(_enc_name);
  }

  const FancyString FancyEncoding::inspect() const
  {
    return FancyString("<Encoding:"+_enc_name+">");
  }

  string FancyEncoding::name() const
  {
    return _enc_name;
  }

}

/* eof */