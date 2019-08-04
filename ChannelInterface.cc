#include "ChannelInterface.h"

//构造
ChannelInterface::ChannelInterface() : del_flag(false) {
}

//析构
ChannelInterface::~ChannelInterface() {
}

//设置删除标签
void ChannelInterface::SetDelFlag() {
  del_flag = true;
}

//判断是否需要删除
bool ChannelInterface::NeedDel() {
  return del_flag;
}
