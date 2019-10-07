// File name: ExtremeC_examples_chapter9_3.cpp
// Description: Multiple inheritance in C++

#include <string.h>

class A {
public:
  char a;
  char b[4];
};

class B {
public:
  char c;
  char d;
};

class C {
public:
  char e;
  char f;
};

class D : public A, public B, public C {
public:
  char str[5];
};

int main(int argc, char** argv) {
  D d;
  d.a = 'A';
  strcpy(d.b, "BBB");
  d.c = 'C';
  d.d = 'D';
  d.e = 'E';
  d.f = 'F';
  strcpy(d.str, "1234");
  A* ap = &d;
  B* bp = &d;
  C* cp = &d;
  D* dp = &d;
  // We need to set a break point at this line.
  return 0;
}
