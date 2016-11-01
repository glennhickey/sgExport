# this library only used as submodule that relies on include.mk in parent directory. 
rootPath=..
include ${rootPath}/include.mk

sidegraphInc = sidegraph.h sgcommon.h sgsequence.h sgposition.h sgside.h sgjoin.h sgsegment.h side2seq.h

all : sgExport.a 

clean : 
	rm -f  sidegraph.o sglookup.o md5.o sgsql.o side2seq.o sgExport.a
	cd tests && make clean

unitTests : sgExport.a
	cd tests && make

sidegraph.o : sidegraph.cpp ${sidegraphInc}
	${cpp} ${cppflags} -I . sidegraph.cpp -c

sglookup.o : sglookup.cpp sglookup.h ${sidegraphInc}
	${cpp} ${cppflags} -I . sglookup.cpp -c

md5.o : md5.cpp md5.h
	${cpp} ${cppflags} -I . md5.cpp -c

sgsql.o : sgsql.cpp md5.h sgsql.h sglookup.h ${sidegraphInc}
	${cpp} ${cppflags} -I . sgsql.cpp -c

side2seq.o: side2seq.cpp side2seq.h  ${sidegraphInc}
	${cpp} ${cppflags} -I. side2seq.cpp -c

sgExport.a : sidegraph.o sglookup.o md5.o sgsql.o side2seq.o
	ar rc sgExport.a sidegraph.o sglookup.o md5.o sgsql.o side2seq.o

test : unitTests
	tests/unitTests
