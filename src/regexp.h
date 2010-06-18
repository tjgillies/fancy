#ifndef _REGEX_H_
#define _REGEX_H_

#include "fancy_object.h"
#include "string.h"

namespace fancy {

  /**
   * Regexpp class representing Regular Expression Objects in Fancy.
   */
  class Regexp : public FancyObject
  {
  public:
    /**
     * Regexp constructor.
     * @param pattern A C++ string that is the regexp pattern.
     */
    Regexp(const string &pattern);
    ~Regexp();

    /**
     * See FancyObject for these methods.
     */  
    virtual FancyObject* equal(FancyObject* other) const;
    virtual EXP_TYPE type() const;
    virtual const FancyString to_s() const;

    /**
     * Returns the pattern string.
     * @return C++ pattern string.
     */
    string pattern() const;

    /**
     * Does the matching on a given string.
     * @param string The string to match this regular expression
     * against.
     * @return The match value (e.g. nil, if none match or the array
     * with matches).
     */
    FancyObject* match(FancyString* string) const;

  private:
    string _pattern;
  };

}

#endif /* _REGEX_H_ */
