#include "socket_error.h"
#include <string>
#include <iostream>

SocketError::SocketError(const std::string & msg) {
    this->msg = msg;
}

const char * SocketError::what(void) const noexcept {
    return this->msg.c_str();
}

SocketError::~SocketError(void) noexcept {
}
