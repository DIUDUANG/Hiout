#include "HioutKernel.h"
#include <unistd.h>
#include <cstdio>
#include <sys/epoll.h>
#include "ChannelInterface.h"

namespace {
constexpr int EPOLL_LISTEN_MAX = 100;
}

//静态成员初始化
int HioutKernel::m_epoll_fd = -1;
std::list<ChannelInterface*> HioutKernel::channel_list;

//初始化框架,每个项目必须调用一次
bool HioutKernel::Init() {
  bool ret = false;
  int fd = epoll_create(1);
  if (fd > 0) {
    m_epoll_fd = fd;
    ret = true;
  }

  return ret;
}

//反初始化框架,退出程序前调用
void HioutKernel::Fini() {
  //从epoll树上删除监听的套接字并从内核中删除
  for (auto& fd : channel_list) {
    epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, fd->GetFd(), nullptr);
    channel_list.remove(fd);
  }

  //关闭epoll树的句柄
  close(m_epoll_fd);
  m_epoll_fd = -1;
}

//运行框架
void HioutKernel::Run() {
  if (m_epoll_fd < 0) {
    return;
  }

  //epoll_wait循环监听
  while (1) {
    epoll_event tmp_events[EPOLL_LISTEN_MAX];
    int count = epoll_wait(m_epoll_fd, 
                           tmp_events, 
                           sizeof(tmp_events) / sizeof(tmp_events[0]), 
                           -1);

    //永久监听不会监听到0个变化
    if (0 == count) {
      break;
    }
    //监听错误,判断错误情况
    if (count < 0) {
      if (EINTR == errno) {
        continue;
      }

      else {
        break;
      }
    }

    //监听正常
    for (int i = 0; i < count; ++i) {
      auto pChannel = static_cast<ChannelInterface*>(tmp_events[i].data.ptr);
      //判断是否有读事件
      if (EPOLLIN & tmp_events[i].events) {
        std::string tmp_string = pChannel->ReadFd();
        //读取失败就设置删除标签
        if (false == pChannel->Process(tmp_string)) {
          pChannel->SetDelFlag();
        }
      }

      //判断是否有写事件
      if (EPOLLOUT & tmp_events[i].events) {
        int read_count = pChannel->WriteFd(pChannel->output_buf);
        //判断是否读取完毕,弹出已经读取的buf
        if (read_count < pChannel->output_buf.size()) {
          pChannel->output_buf.erase(pChannel->output_buf.begin(),
                                     pChannel->output_buf.begin() + read_count);
        }
        else {
          //若全部读取完毕,则停止监控写事件并清空缓冲区
          ChannelOutDel(pChannel);
          pChannel->output_buf.clear();
        }
      }

      //判断是否需要摘取通道
      if (pChannel->NeedDel()) {
        DelChannel(pChannel);
        delete pChannel;
      }
    }
  }
}

//向内核中添加通道,参数请传入堆对象
bool HioutKernel::AddChannel(ChannelInterface* _pChannel) {
  bool ret = false;
  if (nullptr == _pChannel) {
    return ret;
  }

  //上epoll树
  epoll_event tmp_event;
  tmp_event.events = EPOLLIN;
  tmp_event.data.ptr = _pChannel;
  int retval = epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, _pChannel->GetFd(), &tmp_event);
  if (0 == retval) {
      ret = true;
      //添加通道到内核中
      channel_list.push_back(_pChannel);
  }

  return ret;
}

//从内核中摘出通道,参数请传入堆对象
void HioutKernel::DelChannel(ChannelInterface* _pChannel) {
  bool ret = false;
  if (nullptr == _pChannel) {
    return;
  }

  //从epoll中摘除该通道
  epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, _pChannel->GetFd(), nullptr);
  //从内核中删除该通道
  channel_list.remove(_pChannel);
}
//关闭监听写事件
void HioutKernel::ChannelOutDel(ChannelInterface* _pChannel) {
  epoll_event tmp_event;
  tmp_event.events = EPOLLIN;
  tmp_event.data.ptr = _pChannel;
  epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, _pChannel->GetFd(), &tmp_event);
}

//添加EPOLLOUT监听事件
bool HioutKernel::ChannelOutAdd(ChannelInterface* _pChannel) {
  bool ret = false;
  if (nullptr == _pChannel) {
    return ret;
  }
  //epoll添加EPOLLOUT事件
  epoll_event tmp_event;
  tmp_event.events = EPOLLIN | EPOLLOUT;
  tmp_event.data.ptr = _pChannel;
  epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, _pChannel->GetFd(), &tmp_event);

  return ret;
}

//构造
HioutKernel::HioutKernel() {
}

//析构
HioutKernel::~HioutKernel() {
}
