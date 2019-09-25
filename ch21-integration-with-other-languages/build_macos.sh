set -x

clang -c -g -fPIC cstack.c -o cstack.o
clang -dynamiclib cstack.o -o libcstack.dylib

clang -c -g cstack_tests.c -o tests.o
clang tests.o -lcstack -L. -o cstack_tests.out
