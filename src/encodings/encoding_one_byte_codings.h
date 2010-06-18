#ifndef _FANCY_ENCODING_ONE_BYTE_
#define _FANCY_ENCODING_ONE_BYTE_


namespace fancy {
  /**
   * String class representing String objects within Fancy.
   */
  class FancyEncodingOneByte : public FancyEncoding
  {
  public:
    FancyEncodingOneByte();

    virtual FancyEncoding *clone() const;

    FancyString *substr(const FancyString *str,int start,int end) const;
    int strlen(const FancyString *str) const;
    FancyString *characterAt(const FancyString *str,int index) const;
    FancyString *downcase(const FancyString *str) const;
    FancyString *upcase(const FancyString *str) const;

  };
}

#endif /* _FANCY_ENCODING_ONE_BYTE_ */
