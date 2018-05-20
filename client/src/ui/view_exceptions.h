#ifndef __COMMON_EXCEPTIONS_H__
#define __COMMON_EXCEPTIONS_H__

#include <iostream>
#include <typeinfo>
#include <errno.h>
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include <string>
#include "view_exceptions_messages.h"

#define ERR_BUFF_LEN 512

namespace View {
  class Exception : public std::exception {
    private:
      char msg_error[ERR_BUFF_LEN];
      int _errno;

    public:
      explicit Exception(const char* fmt, ...) noexcept;
      virtual const char *what() const noexcept;
      virtual ~Exception() noexcept;
  };
}


#endif
