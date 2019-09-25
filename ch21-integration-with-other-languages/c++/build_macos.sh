set -x

clang++ -c -g -std=c++11 -I$PWD/.. Stack.cpp -o Stack.o
clang++ -L$PWD/.. Stack.o -lcstack -o cstack_cpp.out
