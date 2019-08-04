#ifndef __HIOUT_STDOUTCHANNEL_H__
#define __HIOUT_STDOUTCHANNEL_H__
#include "ChannelInterface.h"

//标准输出类
class StdoutChannel : public ChannelInterface {
  // 通过 ChannelInterface 继承
  virtual int WriteFd(std::string _input) override;
  virtual std::string ReadFd() override;
  virtual int GetFd() override;
  virtual bool Process(std::string _input) override;
  virtual bool SendOut(std::string _output) override;
};

#endif
