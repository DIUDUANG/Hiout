#include "ChannelInterface.h"

//����
ChannelInterface::ChannelInterface() : del_flag(false) {
}

//����
ChannelInterface::~ChannelInterface() {
}

//����ɾ����ǩ
void ChannelInterface::SetDelFlag() {
  del_flag = true;
}

//�ж��Ƿ���Ҫɾ��
bool ChannelInterface::NeedDel() {
  return del_flag;
}
