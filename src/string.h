#ifndef _FANCY_STRING_H_
#define _FANCY_STRING_H_

#include "fancy_object.h"


namespace fancy {

  class FancyEncoding;
  class Number;

  /**
   * String class representing String objects within Fancy.
   */
  class FancyString : public FancyObject
  {
  public:
    /**
     * FancyString constructor.
     * @param value C++ string containing the actual string.
     */
    FancyString(const string &value);
    FancyString(const unsigned char* value);
    FancyString(const unsigned char value);
    FancyString(const FancyString &str);
    ~FancyString();

    static unsigned char *normalize(const unsigned char *chr,size_t *bytes);

    /**
     * See FancyObject for these methods.
     */
    virtual FancyObject* equal(FancyObject* other) const;
    virtual EXP_TYPE type() const;
    virtual const FancyString to_s() const;
    virtual const FancyString inspect() const;

    /**
     * Returns the C string value.
     * @return The C string value.
     */
    const unsigned char *value() const;

    /**
     * Returns the encoding of the string
     * @return The encoding of the string
     */
    const FancyEncoding *encoding() const;

    size_t bytes() const;

    /**
     * Returns a FancyString object with a given C++ string value.
     * FancyStrings in Fancy get cached, since they're immutable.
     * Multiple occurances of the same FancyString in Fancy use the same
     * FancyString object.
     * @param value C++ string value.
     * @return A FancyString object with a given C++ string value.
     */
    static FancyString* from_value(const unsigned char *value);
    static FancyString* from_value(const string &value);


    FancyString *substr(int start,int end) const;
    int strlen() const;
    FancyString *characterAt(int index) const;
    Number *codePointAt(int index) const;
    FancyString *downcase() const;
    FancyString *upcase() const;

  private:
    size_t _bytes;
    unsigned char *_value;
    FancyEncoding *_encoding;

    //static map<string, FancyString*> value_cache;
  };

}

#endif /* _FANCY_STRING_H_ */
