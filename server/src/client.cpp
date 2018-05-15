#include <iostream>
#include "client.h"
#include "../../client/src/protocol.h"

Client::Client(Protocol prt) :
protocol(std::move(prt)){
    this->status = lobby;
}
