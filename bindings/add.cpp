// addon.cc
#include <node.h>
#include <string>
#include "person.h"
#include <iostream>
using namespace std;
namespace demo {

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

// This is the implementation of the "add" method
// Input arguments are passed using the
// const FunctionCallbackInfo<Value>& args struct
void Add(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  // Check the number of arguments passed.
  if (args.Length() < 2) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  // Check the argument types
  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  // Perform the operation
  double value = args[0]->NumberValue() + args[1]->NumberValue();
  Local<Number> num = Number::New(isolate, value);
  //std::cout<<"Local<Number> new = "<<Number::New(isolate,value)<<std::endl;
  Person aaron;
  //aaron.year;
  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate,"name"),String::NewFromUtf8(isolate,"Aaron"));
  obj->Set(String::NewFromUtf8(isolate,"year"),Number::New(isolate,aaron.year));

  //Local<Person> person;
  //Local<Person> person = Object::New(isolate);
  //person->Set(String::NewFromUtf8(isolate,"name"),String::New(isolate,"name"));
  //person->Set(Number::New(isolate,"year"),Number::New(isolate,4));
  // Seteturn value (using the passed in
  // FunctionCallbackInfo<Value>&)
  args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(addon, Init)

}  // namespace demo
