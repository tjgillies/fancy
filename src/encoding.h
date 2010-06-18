#ifndef _FANCY_ENCODING_H_
#define _FANCY_ENCODING_H_

#include "fancy_object.h"
namespace fancy {
  class Number;

  /**
   * String class representing String objects within Fancy.
   */
  class FancyEncoding : public FancyObject
  {
  public:
    /**
     * abstract FancyEncoding constructor. We don't want to get it created! It is just a base class.
     */
    FancyEncoding(const string encoding);
    virtual ~FancyEncoding();

    virtual FancyObject* equal(const FancyObject* other);

    EXP_TYPE type() const;
    virtual const FancyString to_s() const;
    virtual const FancyString inspect() const;
    string name() const;

    virtual FancyEncoding *clone() const;

    virtual FancyString *substr(const FancyString *str,int start,int end) const = 0;
    virtual int strlen(const FancyString *str) const = 0;
    virtual FancyString *characterAt(const FancyString *str,int index) const = 0;
    virtual Number *codePointAt(const FancyString *str,int index) const = 0;
    virtual FancyString *downcase(const FancyString *str) const = 0;
    virtual FancyString *upcase(const FancyString *str) const = 0;

    static FancyString *convert(const FancyString *str,const string from,const string *to);

  protected:
    string _enc_name;
  };
}

#endif /* _FANCY_ENCODING_H_ */
