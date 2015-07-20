rootPath = ../..
include ${rootPath}/include.mk
basePath = ..

all : unitTests

clean :
	rm -f *.o unitTests

unitTests : CuTest.o unitTests.o sidegraphTests.o sglookupTests.o 

CuTest.o : CuTest.h CuTest.c
	${cxx} ${cflags} -c CuTest.c	

unitTests.o : unitTests.h unitTests.cpp
	${cpp} ${cppflags} -I${basePath}/ unitTests.cpp -c

sidegraphTests.o : sidegraphTests.cpp ${basePath}/*.h
	${cpp} ${cppflags} -I${basePath}/ sidegraphTests.cpp -c

sglookupTests.o : sglookupTests.cpp ${basePath}/*.h
	${cpp} ${cppflags} -I${basePath}/ sglookupTests.cpp -c

unitTests : CuTest.o unitTests.o sidegraphTests.o sglookupTests.o ${basePath}/sgExport.a
	${cpp} -I${basePath}/ ${cppflags}  unitTests.o sidegraphTests.o sglookupTests.o ${basePath}/sgExport.a CuTest.o -o unitTests

