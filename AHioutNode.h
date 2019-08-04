#ifndef __HIOUT_AHIOUTHANDLER_H__
#define __HIOUT_AHIOUTHANDLER_H__

//��Ϣ������
class Message;

//��������
class AHioutHandler {
 public:
  //�����ڴ���,��������������,����ֵ���������
  virtual Message* InternelHandle(Message* _input) = 0;
  //��һ������,��������������,����ֵʱ��һ��������
  virtual AHioutHandler* GetNextHandler(Message* _input) = 0;
  //���������
  void Handle(Message* _input);

};

#endif
