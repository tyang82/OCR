#include <node.h>
#include "person.h"
using namespace v8;

void TestingMethod(const FunctionCallbackInfo<Value>& args) {
  printf("We entered testing method.  This is pretty hype\n");
}

void OtherMethod(const FunctionCallbackInfo<Value>& args) {
  printf("The second method entered.\n");
  Person* aaron = new Person();
}

void init(Local<Object> exports){

  NODE_SET_METHOD(exports,"hype",TestingMethod);//this is the mapping
  NODE_SET_METHOD(exports,"madhype",OtherMethod);
}

NODE_MODULE(addon,init)
