#ifndef __HIOUT_AHIOUTHANDLER_H__
#define __HIOUT_AHIOUTHANDLER_H__

//��Ϣ������
class Message;

//��������
class AHioutHandler {
  //�����ڴ���,������������Ϣ,����ֵʱ�������Ϣ
  virtual Message* InternelHandle(Message* _input) = 0;
  //��һ��������,������������Ϣ,����ֵʱ��һ��������
  virtual AHioutHandler* GetNextHandle(Message* _input) = 0;

  //���������
  void Handle(Message* _input);

};

#endif
