g++ -c -std=c++11 -I.. Stack.cpp -o Stack.o
g++ -L../build Stack.o -lcstack -o cstack_cpp.out
