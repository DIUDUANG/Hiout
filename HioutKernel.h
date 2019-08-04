#ifndef __HIOUT_HIOUTKERNEL_H__
#define __HIOUT_HIOUTKERNEL_H__
#include <list>

//ͨ��������
class ChannelInterface;

//��ܺ��Ĵ�����
class HioutKernel {
 public:
  //��ܳ�ʼ��
  static bool Init();
  //���ȥ��ʼ��
  static void Fini();
  //���п��
  static void Run();

  //���ͨ����,���������������ָ��
  static bool AddChannel(ChannelInterface* _pChannel);
  //ժ��ͨ����,���������������ָ��
  static void DelChannel(ChannelInterface* _pChannel);

  //�ر�epoll����д�¼�
  static void ChannelOutDel(ChannelInterface* _pChannel);
  //���epoll�����¼�
  static bool ChannelOutAdd(ChannelInterface* _pChannel);

 private:
  HioutKernel();
  virtual ~HioutKernel();
  
  //epoll��������
  static int m_epoll_fd;
  //ͨ�����¼����
  static std::list<ChannelInterface*> channel_list;
};



#endif
