#include "StdoutChannel.h"
#include <unistd.h>
#include <iostream>

int StdoutChannel::WriteFd(std::string _input) {
  std::cout << '-' << _input << std::endl;
  return 0;
}

std::string StdoutChannel::ReadFd() {
  return std::string();
}

int StdoutChannel::GetFd() {
  return STDOUT_FILENO;
}

bool StdoutChannel::Process(std::string _input) {
  return false;
}

bool StdoutChannel::SendOut(std::string _output) {
  return false;
}
