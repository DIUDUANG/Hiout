#include <iostream>
#include "HioutKernel.h"
#include "StdinChannel.h"

int main(int argc, char** argv) {
  
  StdinChannel* stdin1 = new StdinChannel();
  if (true == HioutKernel::Init()) {
    if (true != HioutKernel::AddChannel(stdin1)) {
      return -1;
    }
  }
  HioutKernel::Run();
  HioutKernel::Fini();

  getchar();

  return 0;
}