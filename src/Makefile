cc = g++
cc_flags = -g -Wall -ansi -pedantic

parser_node_files = identifier expression_list array_literal		\
assignment return require block_literal class_definition hash_literal	\
message_send operator_send method_definition class_method_definition	\
operator_definition class_operator_definition try_catch_block super

parser_files = parser/lex parser/bison

bootstrap_files = core_classes object class block string number		\
console array file directory scope hash exception method system

files = fancy_object true nil hash array symbol number string		\
native_method scope lexical_scope class errors method regexp block	\
utils file directory fancy_exception

src_files = $(foreach file, $(files), $(file).cc) 			\
$(foreach file, $(bootstrap_files), bootstrap/$(file).cc) 		\
$(foreach file, $(parser_files), $(file).c) 				\
parser/parser.cc							\
$(foreach file, $(parser_node_files), parser/nodes/$(file).cc) main.cc

obj_files = $(foreach file, $(files), $(file).o) 			\
$(foreach file, $(bootstrap_files), bootstrap/$(file).o) 		\
$(foreach file, $(parser_files), $(file).o) 				\
parser/parser.o								\
$(foreach file, $(parser_node_files), parser/nodes/$(file).o) main.o

sub_dirs = parser bootstrap

GCLIB = ../vendor/gc/.libs/libgccpp.a ../vendor/gc/.libs/libgc.a

all: subdirs ../bin/fancy

../bin/fancy: $(obj_files)
	@mkdir -p ../bin/
	$(cc) $(cc_flags) $(obj_files) $(GCLIB) -o ../bin/fancy -lfl

main.o: $(foreach file, $(src_files), $(file)) parser/fancy.lex parser/fancy.y
	$(cc) $(cc_flags) -c main.cc -o main.o

fancy_object.o: fancy_object.cc
	$(cc) $(cc_flags) -c fancy_object.cc -o fancy_object.o

true.o: true.cc
	$(cc) $(cc_flags) -c true.cc -o true.o

nil.o: nil.cc
	$(cc) $(cc_flags) -c nil.cc -o nil.o

hash.o: hash.cc
	$(cc) $(cc_flags) -c hash.cc -o hash.o

array.o: array.cc
	$(cc) $(cc_flags) -c array.cc -o array.o

regexp.o: regexp.cc
	$(cc) $(cc_flags) -c regexp.cc -o regexp.o

symbol.o: symbol.cc
	$(cc) $(cc_flags) -c symbol.cc -o symbol.o

number.o: number.cc
	$(cc) $(cc_flags) -c number.cc -o number.o

string.o: string.cc
	$(cc) $(cc_flags) -c string.cc -o string.o

native_method.o: native_method.cc
	$(cc) $(cc_flags) -c native_method.cc -o native_method.o

scope.o: scope.cc
	$(cc) $(cc_flags) -c scope.cc -o scope.o

lexical_scope.o: lexical_scope.cc
	$(cc) $(cc_flags) -c lexical_scope.cc -o lexical_scope.o

class.o: class.cc
	$(cc) $(cc_flags) -c class.cc -o class.o

errors.o: errors.cc
	$(cc) $(cc_flags) -c errors.cc -o errors.o

method.o: method.cc
	$(cc) $(cc_flags) -c method.cc -o method.o

block.o: block.cc
	$(cc) $(cc_flags) -c block.cc -o block.o

utils.o: utils.cc
	$(cc) $(cc_flags) -c utils.cc -o utils.o

file.o: file.cc
	$(cc) $(cc_flags) -c file.cc -o file.o

fancy_exception.o: fancy_exception.cc
	$(cc) $(cc_flags) -c fancy_exception.cc -o fancy_exception.o

subdirs:
	$(foreach dir, $(sub_dirs), cd $(dir) && make && cd ..;)

clean:
	cd parser && make clean > /dev/null
	cd bootstrap && make clean > /dev/null
	rm -f *.o > /dev/null
