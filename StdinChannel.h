#ifndef __HIOUT_STDINCHANNEL_H__
#define __HIOUT_STDINCHANNEL_H__
#include "ChannelInterface.h"

//标准输入通道类
class StdinChannel : public ChannelInterface {
  // 通过 ChannelInterface 继承
  virtual int WriteFd(std::string _input) override;
  virtual std::string ReadFd() override;
  virtual int GetFd() override;
  virtual bool Process(std::string _input) override;
  virtual bool SendOut(std::string _output) override;
};


#endif
