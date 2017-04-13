#include "sharp_blue.h"
#include <iostream>
#include <math.h> 

void Update(double dt) {
  static unsigned char frame = 0;
  if ((++frame)>=60) {
    std::cout << "fps:" << floor(1.0 / dt) << std::endl;
    frame = 0;
  }
}


int main(int argc, char *argv[]) {
  std::cout << "hello world" << std::endl;
  sb::version();
  if(!sb::init()){
    return 1;
  }
  sb::SetTickFunc(Update);
  sb::Start();
  std::cout << "Goodbye from GameCode" << std::endl;
  return 0;
}

