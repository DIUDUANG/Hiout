#ifndef __HIOUT_IODIRECTION_H__
#define __HIOUT_IODIRECTION_H__
#include "Message.h"

//��ʾ��Ϣ��ͨ�������
class IODirection : public Message{
 public:
   enum HioutIODIRECTION {
     IN,
     OUT
   }m_dir;

  IODirection(HioutIODIRECTION _dir);



};

#endif
