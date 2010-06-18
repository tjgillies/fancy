#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "fancy_object.h"


namespace fancy {

  #define INT_CACHE_SIZE 1000

  /**
   * Number class representing Number objects (both double and
   * integer) in Fancy.
   */
  class Number : public FancyObject
  {
  public:
    /**
     * Number constructor for double value.
     * @param value Double value for Number.
     */
    Number(double value);

    /**
     * Number constructor for int value.
     * @param value Integer value for Number.
     */
    Number(int value);
    ~Number();

    /**
     * See FancyObject for these methods.
     */  
    virtual FancyObject* equal(FancyObject* other) const;
    virtual EXP_TYPE type() const;
    virtual const FancyString to_s() const;

    /**
     * Indicates, if Number is double.
     * @return true if double, false otherwise.
     */
    bool is_double() const;

    /**
     * Returns the double value (casted, if needed).
     * @return Double value for the Number.
     */
    double doubleval() const;

    /**
     * Returns the int value (casted, if needed).
     * @return Integer value for the Number.
     */
    int intval() const;
  
    /**
     * Returns Number object with the given int value.
     * @param value Integer value for the Number object.
     * @return Number object with the given value.
     */
    static Number* from_int(int value);

    /**
     * Returns Number object with the given double value.
     * @param value Double value for the Number object.
     * @return Number object with the given value.
     */
    static Number* from_double(double value);

    /**
     * Initializes the number cache with the first INT_CACHE_SIZE integer Numbers.
     */
    static void init_cache();

  private:
    int _intval;
    double _doubleval;
    bool _is_double;

    static Number** int_cache;
  };

}

#endif /* _NUMBER_H_ */
