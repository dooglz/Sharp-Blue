#include "sharp_blue.h"
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "hello world" << std::endl;
  sb::version();
  if(!sb::init()){
    return 1;
  }
  sb::Start();
  std::cout << "Goodbye from GameCode" << std::endl;
  return 0;
}

