#include "HioutKernel.h"
#include <unistd.h>
#include <cstdio>
#include <sys/epoll.h>
#include "ChannelInterface.h"

namespace {
constexpr int EPOLL_LISTEN_MAX = 100;
}

//��̬��Ա��ʼ��
int HioutKernel::m_epoll_fd = -1;
std::list<ChannelInterface*> HioutKernel::channel_list;

//��ʼ�����,ÿ����Ŀ�������һ��
bool HioutKernel::Init() {
  bool ret = false;
  int fd = epoll_create(1);
  if (fd > 0) {
    m_epoll_fd = fd;
    ret = true;
  }

  return ret;
}

//����ʼ�����,�˳�����ǰ����
void HioutKernel::Fini() {
  //��epoll����ɾ���������׽��ֲ����ں���ɾ��
  for (auto& fd : channel_list) {
    epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, fd->GetFd(), nullptr);
    channel_list.remove(fd);
  }

  //�ر�epoll���ľ��
  close(m_epoll_fd);
  m_epoll_fd = -1;
}

//���п��
void HioutKernel::Run() {
  if (m_epoll_fd < 0) {
    return;
  }

  //epoll_waitѭ������
  while (1) {
    epoll_event tmp_events[EPOLL_LISTEN_MAX];
    int count = epoll_wait(m_epoll_fd, 
                           tmp_events, 
                           sizeof(tmp_events) / sizeof(tmp_events[0]), 
                           -1);

    //���ü������������0���仯
    if (0 == count) {
      break;
    }
    //��������,�жϴ������
    if (count < 0) {
      if (EINTR == errno) {
        continue;
      }

      else {
        break;
      }
    }

    //��������
    for (int i = 0; i < count; ++i) {
      auto pChannel = static_cast<ChannelInterface*>(tmp_events[i].data.ptr);
      //�ж��Ƿ��ж��¼�
      if (EPOLLIN & tmp_events[i].events) {
        std::string tmp_string = pChannel->ReadFd();
        //��ȡʧ�ܾ�����ɾ����ǩ
        if (false == pChannel->Process(tmp_string)) {
          pChannel->SetDelFlag();
        }
      }

      //�ж��Ƿ���д�¼�
      if (EPOLLOUT & tmp_events[i].events) {
        int read_count = pChannel->WriteFd(pChannel->output_buf);
        //�ж��Ƿ��ȡ���,�����Ѿ���ȡ��buf
        if (read_count < pChannel->output_buf.size()) {
          pChannel->output_buf.erase(pChannel->output_buf.begin(),
                                     pChannel->output_buf.begin() + read_count);
        }
        else {
          //��ȫ����ȡ���,��ֹͣ���д�¼�����ջ�����
          ChannelOutDel(pChannel);
          pChannel->output_buf.clear();
        }
      }

      //�ж��Ƿ���Ҫժȡͨ��
      if (pChannel->NeedDel()) {
        DelChannel(pChannel);
        delete pChannel;
      }
    }
  }
}

//���ں������ͨ��,�����봫��Ѷ���
bool HioutKernel::AddChannel(ChannelInterface* _pChannel) {
  bool ret = false;
  if (nullptr == _pChannel) {
    return ret;
  }

  //��epoll��
  epoll_event tmp_event;
  tmp_event.events = EPOLLIN;
  tmp_event.data.ptr = _pChannel;
  int retval = epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, _pChannel->GetFd(), &tmp_event);
  if (0 == retval) {
      ret = true;
      //���ͨ�����ں���
      channel_list.push_back(_pChannel);
  }

  return ret;
}

//���ں���ժ��ͨ��,�����봫��Ѷ���
void HioutKernel::DelChannel(ChannelInterface* _pChannel) {
  bool ret = false;
  if (nullptr == _pChannel) {
    return;
  }

  //��epoll��ժ����ͨ��
  epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, _pChannel->GetFd(), nullptr);
  //���ں���ɾ����ͨ��
  channel_list.remove(_pChannel);
}
//�رռ���д�¼�
void HioutKernel::ChannelOutDel(ChannelInterface* _pChannel) {
  epoll_event tmp_event;
  tmp_event.events = EPOLLIN;
  tmp_event.data.ptr = _pChannel;
  epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, _pChannel->GetFd(), &tmp_event);
}

//���EPOLLOUT�����¼�
bool HioutKernel::ChannelOutAdd(ChannelInterface* _pChannel) {
  bool ret = false;
  if (nullptr == _pChannel) {
    return ret;
  }
  //epoll���EPOLLOUT�¼�
  epoll_event tmp_event;
  tmp_event.events = EPOLLIN | EPOLLOUT;
  tmp_event.data.ptr = _pChannel;
  epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, _pChannel->GetFd(), &tmp_event);

  return ret;
}

//����
HioutKernel::HioutKernel() {
}

//����
HioutKernel::~HioutKernel() {
}
