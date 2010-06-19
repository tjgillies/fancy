# continuation example

x = self callcc: |cont| {
  0 upto: 30 do_each: |i| {
  #  i println;
    (i > 10) if_true: {
      cont call: i
    }
  }
};

x println # prints: 11
