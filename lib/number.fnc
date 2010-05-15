def class Number {
  def squared {
    self * self
  }

  def abs {
    self < 0 if_true: {
      self * -1
    } else: {
      self
    }
  }

  def negate {
    self * -1
  }

  def even? {
    self modulo: 2 . == 0
  }

  def odd? {
    self even? not
  }

  def upto: val {
    coll = [];
    tmp = self;
    { tmp <= val } while_true: {
      coll << tmp;
      tmp = tmp + 1
    };
    coll
  }

  def downto: val {
    coll = [];
    tmp = self;
    { tmp >= val } while_true: {
      coll << tmp;
      tmp = tmp - 1
    };
    coll
  }

  def upto: val do_each: block {
    tmp = self;
    { tmp <= val } while_true: {
      block call: tmp;
      tmp = tmp + 1
    }
  }
};

def class Enumerable {
  def sum {
    self reduce: |x y| { x + y } with: 0
  }

  def product {
    self reduce: |x y| { x * y } with: 1
  }
}

