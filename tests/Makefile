rootPath = ../..
include ${rootPath}/include.mk
basePath = ..

all : unitTests

clean :
	rm -f *.o unitTests

unitTests : CuTest.o unitTests.o sidegraphTests.o sglookupTests.o side2seqTests.o

CuTest.o : CuTest.h CuTest.c
	${cxx} ${cflags} -c CuTest.c	

unitTests.o : unitTests.h unitTests.cpp
	${cpp} ${cppflags} -I${basePath}/ unitTests.cpp -c

sidegraphTests.o : sidegraphTests.cpp ${basePath}/*.h
	${cpp} ${cppflags} -I${basePath}/ sidegraphTests.cpp -c

sglookupTests.o : sglookupTests.cpp ${basePath}/*.h
	${cpp} ${cppflags} -I${basePath}/ sglookupTests.cpp -c

side2seqTests.o : side2seqTests.cpp ${rootPath}/*.h
	${cpp} ${cppflags} -I ${sgExportPath}/tests -I${rootPath}/ side2seqTests.cpp -c

unitTests : CuTest.o unitTests.o sidegraphTests.o sglookupTests.o side2seqTests.o ${basePath}/sgExport.a
	${cpp} -I${basePath}/ ${cppflags}  unitTests.o sidegraphTests.o sglookupTests.o side2seqTests.o ${basePath}/sgExport.a CuTest.o -o unitTests

