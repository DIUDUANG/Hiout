#ifndef __HIOUT_CHANNELINTERFACE_H__
#define __HIOUT_CHANNELINTERFACE_H__
#include <string>

//通道抽象类
class ChannelInterface {
 public:
  //缓冲区
  std::string output_buf;

 protected:
  //接口类的构造和析构函数,应为protected权限
  ChannelInterface();
  virtual ~ChannelInterface();

 private:
  //向文件描述符写入数据
  virtual int WriteFd(std::string _input) = 0;
  //从文件描述符读取数据
  virtual std::string ReadFd() = 0;
  //获取文件描述符
  virtual int GetFd() = 0;
  //处理函数
  virtual bool Process(std::string _input) = 0;
  //发送函数
  virtual bool SendOut(std::string _output) = 0;
  //设置删除标签
  void SetDelFlag();
  //判断是否处于需要删除的状态
  bool NeedDel();
  //删除标签
  bool del_flag;

  friend class HioutKernel;
};

#endif
