cc = g++
cc_flags = -g -Wall -ansi -pedantic

files = encoding_utf8 encoding_utf16 encoding_utf32 encoding_one_byte_codings

src_files = $(foreach file, $(files), $(file).cc)
obj_files = $(foreach file, $(files), $(file).o)

sub_dirs = 

all: subdirs $(obj_files)

encoding_utf8.o: encoding_utf8.cc encoding_utf8.h
	$(cc) $(cc_flags) `icu-config --cflags` -c encoding_utf8.cc -o encoding_utf8.o

encoding_utf16.o: encoding_utf16.cc encoding_utf16.h
	$(cc) $(cc_flags) `icu-config --cflags` -c encoding_utf16.cc -o encoding_utf16.o

encoding_utf32.o: encoding_utf32.cc encoding_utf32.h
	$(cc) $(cc_flags) `icu-config --cflags` -c encoding_utf32.cc -o encoding_utf32.o

encoding_one_byte_codings.o: encoding_one_byte_codings.cc encoding_one_byte_codings.h
	$(cc) $(cc_flags) -c encoding_one_byte_codings.cc -o encoding_one_byte_codings.o

subdirs:
	$(foreach dir, $(sub_dirs), cd $(dir) && make && cd ..;)

clean:
	rm -f *.o > /dev/null
