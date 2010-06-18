#ifndef _FANCY_ENCODING_UTF32_
#define _FANCY_ENCODING_UTF32_


namespace fancy {
  /**
   * String class representing String objects within Fancy.
   */
  class FancyEncodingUTF32 : public FancyEncoding
  {
  public:
    FancyEncodingUTF32();

    virtual FancyEncoding *clone() const;

    FancyString *substr(const FancyString *str,int start,int end) const;
    int strlen(const FancyString *str) const;
    FancyString *characterAt(const FancyString *str,int index) const;
    FancyString *downcase(const FancyString *str) const;
    FancyString *upcase(const FancyString *str) const;

  };
}

#endif /* _FANCY_ENCODING_UTF32_ */
