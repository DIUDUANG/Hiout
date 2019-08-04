#include "StdinChannel.h"
#include <unistd.h>
#include <iostream>
#include <string>

int StdinChannel::WriteFd(std::string _input) {
  return 0;
}

std::string StdinChannel::ReadFd() {
  std::string ret;
  std::cin >> ret;
  return ret;
}

int StdinChannel::GetFd() {
  return STDIN_FILENO;
}

bool StdinChannel::Process(std::string _input) {
  bool ret = false;
  std::cout << '[' << _input << "]" << std::endl;
  ret = true;
  return ret;
}

bool StdinChannel::SendOut(std::string _output) {
  return false;
}
