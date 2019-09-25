set -x

gcc -c -g -fPIC cstack.c -o cstack.o
gcc -shared cstack.o -o libcstack.so

gcc -c -g cstack_tests.c -o tests.o
gcc tests.o -lcstack -L. -o cstack_tests.out
