#include "view_exceptions.h"
#include <errno.h>
#include <cstdio>
#include <cstdarg>

View::Exception::Exception(const char* fmt, ...) noexcept {
  this->_errno = errno;
  
  va_list args;
  va_start(args, fmt);

  int s = vsnprintf(this->msg_error, ERR_BUFF_LEN, fmt, args);
  va_end(args); 

  if (this->_errno) {
    strncpy(this->msg_error+s, strerror(_errno), ERR_BUFF_LEN-s);
  }  

  this->msg_error[ERR_BUFF_LEN-1] = 0;
}

View::Exception::~Exception() {}

const char * View::Exception::what() const noexcept {
  return this->msg_error;
}

