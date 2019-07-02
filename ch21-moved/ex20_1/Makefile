CC = gcc

build: prereq .build/main.o .build/libcalc.a
	${CC} -L.build -lcalc .build/main.o -o .build/ex20_1.out

prereq:
	mkdir -p .build

.build/libcalc.a: .build/add.o .build/multiply.o .build/subtract.o
	ar rcs .build/libcalc.a .build/add.o .build/multiply.o .build/subtract.o

.build/main.o: exec/main.c calc/calc.h
	${CC} -c -Icalc exec/main.c -o .build/main.o

.build/add.o: calc/add.c calc/calc.h
	${CC} -c calc/add.c -o .build/add.o

.build/subtract.o: calc/subtract.c calc/calc.h
	${CC} -c calc/subtract.c -o .build/subtract.o

.build/multiply.o: calc/multiply.c calc/calc.h
	${CC} -c calc/multiply.c -o .build/multiply.o

clean: .build
	rm -rf .build
