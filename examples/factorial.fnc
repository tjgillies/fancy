def class Number {
  def factorial {
    1 upto: self . product
  }
};

1 upto: 10 do_each: |i| {
  i to_s ++ "! = " ++ (i factorial) println
}
