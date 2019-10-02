BUILD_DIR = out
OBJ = ${BUILD_DIR}/calc/add.o \
			${BUILD_DIR}/calc/subtract.o \
			${BUILD_DIR}/calc/multiply.o \
			${BUILD_DIR}/exec/main.o
CC = gcc
HEADER_DIRS = -Icalc
LIBCALCNAME = calc
LIBCALC = ${BUILD_DIR}/lib${LIBCALCNAME}.a
EXEC = ${BUILD_DIR}/ex23_1.out

build: prereq ${BUILD_DIR}/exec/main.o ${LIBCALC}
	${CC} -L${BUILD_DIR} -l${LIBCALCNAME} ${BUILD_DIR}/exec/main.o -o ${EXEC}

prereq:
	mkdir -p ${BUILD_DIR}
	mkdir -p ${BUILD_DIR}/calc
	mkdir -p ${BUILD_DIR}/exec

${LIBCALC}: ${OBJ}
	ar rcs ${LIBCALC} ${OBJ}

${BUILD_DIR}/calc/%.o: calc/%.c
	${CC} -c ${HEADER_DIRS} $< -o $@

${BUILD_DIR}/exec/%.o: exec/%.c
	${CC} -c ${HEADER_DIRS} $< -o $@

clean: ${BUILD_DIR}
	rm -rf ${BUILD_DIR}
