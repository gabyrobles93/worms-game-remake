#include "protocol_error.h"
#include <string>
#include <iostream>

ProtocolError::ProtocolError(const std::string & msg) {
    this->msg = msg;
}

const char * ProtocolError::what(void) const noexcept {
    return this->msg.c_str();
}

ProtocolError::~ProtocolError(void) noexcept {
}
