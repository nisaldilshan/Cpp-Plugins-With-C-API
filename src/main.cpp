// main.cpp
#include "APIClass.h"

APIClass *ptr = nullptr;

extern "C"
{
  MYLIB_EXPORT void initLib()
  {
    ptr = new APIClass();
  }

  MYLIB_EXPORT void closeLib()
  {
    delete ptr;
  }

  MYLIB_EXPORT int add(int a, int b)
  {
    return ptr->add(a, b);
  }
}