#ifndef __HIOUT_AHIOUTHANDLER_H__
#define __HIOUT_AHIOUTHANDLER_H__

//消息类声明
class Message;

//处理者类
class AHioutHandler {
  //本环节处理,参数是输入消息,返回值时输出的消息
  virtual Message* InternelHandle(Message* _input) = 0;
  //下一个处理环节,参数是输入消息,返回值时下一个处理环节
  virtual AHioutHandler* GetNextHandle(Message* _input) = 0;

  //本环节入口
  void Handle(Message* _input);

};

#endif
