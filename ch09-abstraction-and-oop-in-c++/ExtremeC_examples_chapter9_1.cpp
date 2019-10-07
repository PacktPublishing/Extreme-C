// File name: ExtremeC_examples_chapter9_1.cpp
// Description: Rectangle class in C++

#include <iostream>

class Rect {
public:
  int Area() {
    return width * length;
  }
  int width;
  int length;
};

int main(int argc, char** argv) {
  Rect r;
  r.width = 10;
  r.length = 25;
  int area = r.Area();
  std::cout << "Area: " << area << std::endl;
  return 0;
}
