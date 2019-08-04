#ifndef __HIOUT_CHANNELINTERFACE_H__
#define __HIOUT_CHANNELINTERFACE_H__
#include <string>

//ͨ��������
class ChannelInterface {
 public:
  //������
  std::string output_buf;

 protected:
  //�ӿ���Ĺ������������,ӦΪprotectedȨ��
  ChannelInterface();
  virtual ~ChannelInterface();

 private:
  //���ļ�������д������
  virtual int WriteFd(std::string _input) = 0;
  //���ļ���������ȡ����
  virtual std::string ReadFd() = 0;
  //��ȡ�ļ�������
  virtual int GetFd() = 0;
  //������
  virtual bool Process(std::string _input) = 0;
  //���ͺ���
  virtual bool SendOut(std::string _output) = 0;
  //����ɾ����ǩ
  void SetDelFlag();
  //�ж��Ƿ�����Ҫɾ����״̬
  bool NeedDel();
  //ɾ����ǩ
  bool del_flag;

  friend class HioutKernel;
};

#endif
