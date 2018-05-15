#include <iostream>
#include <string>
#include "server_error.h"

ServerError::ServerError(const std::string & msg) {
    this->msg = msg;
}

const char * ServerError::what() const noexcept {
    return this->msg.c_str();
}

ServerError::~ServerError() {
}
