#ifndef __HIOUT_IODIRECTION_H__
#define __HIOUT_IODIRECTION_H__
#include "Message.h"

//表示消息流通方向的类
class IODirection : public Message{
 public:
   enum HioutIODIRECTION {
     IN,
     OUT
   }m_dir;

  IODirection(HioutIODIRECTION _dir);



};

#endif
