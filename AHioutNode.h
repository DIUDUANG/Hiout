#ifndef __HIOUT_AHIOUTHANDLER_H__
#define __HIOUT_AHIOUTHANDLER_H__

//消息类声明
class Message;

//处理者类
class AHioutHandler {
 public:
  //本环节处理,参数是输入数据,返回值是输出数据
  virtual Message* InternelHandle(Message* _input) = 0;
  //下一处理环节,参数是输入数据,返回值时下一个处理者
  virtual AHioutHandler* GetNextHandler(Message* _input) = 0;
  //本环节入口
  void Handle(Message* _input);

};

#endif
