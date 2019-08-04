#include "AHioutHandler.h"
//本环节入口,参数是输入的消息
void AHioutHandler::Handle(Message* _input) {
  
  auto internel_message = InternelHandle(_input);
  if (nullptr != internel_message) {
    auto next = GetNextHandle(_input);
    if (nullptr != next) {
      next->Handle(_input);
    }
  }


}
