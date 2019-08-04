#ifndef __HIOUT_HIOUTKERNEL_H__
#define __HIOUT_HIOUTKERNEL_H__
#include <list>

//通道类声明
class ChannelInterface;

//框架核心处理类
class HioutKernel {
 public:
  //框架初始化
  static bool Init();
  //框架去初始化
  static void Fini();
  //运行框架
  static void Run();

  //添加通道类,参数传入堆区对象指针
  static bool AddChannel(ChannelInterface* _pChannel);
  //摘除通道类,参数传入堆区对象指针
  static void DelChannel(ChannelInterface* _pChannel);

  //关闭epoll监听写事件
  static void ChannelOutDel(ChannelInterface* _pChannel);
  //添加epoll监听事件
  static bool ChannelOutAdd(ChannelInterface* _pChannel);

 private:
  HioutKernel();
  virtual ~HioutKernel();
  
  //epoll红黑树句柄
  static int m_epoll_fd;
  //通道类记录集合
  static std::list<ChannelInterface*> channel_list;
};



#endif
