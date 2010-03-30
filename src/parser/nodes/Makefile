cc = g++
cc_flags = -g -Wall -ansi -pedantic

files = hash_literal array_literal class_definition method_call	\
operator_call assignment method_definition block_literal \

src_files = $(foreach file, $(files), $(file).cc)
obj_files = $(foreach file, $(files), $(file).o)

all: $(obj_files)

hash_literal.o: hash_literal.cc
	$(cc) $(cc_flags) -c hash_literal.cc -o hash_literal.o

array_literal.o: array_literal.cc
	$(cc) $(cc_flags) -c array_literal.cc -o array_literal.o

class_definition.o: class_definition.cc
	$(cc) $(cc_flags) -c class_definition.cc -o class_definition.o

method_call.o: method_call.cc
	$(cc) $(cc_flags) -c method_call.cc -o method_call.o

operator_call.o: operator_call.cc
	$(cc) $(cc_flags) -c operator_call.cc -o operator_call.o

assignment.o: assignment.cc
	$(cc) $(cc_flags) -c assignment.cc -o assignment.o

method_definition.o: method_definition.cc
	$(cc) $(cc_flags) -c method_definition.cc -o method_definition.o

block_literal.o: block_literal.cc
	$(cc) $(cc_flags) -c block_literal.cc -o block_literal.o

clean:
	rm -f *.o > /dev/null