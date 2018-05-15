#include "socket.h"
#include "socket_error.h"
#include "types.h"
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

SocketBase::SocketBase(int sockfd) {
    if (sockfd == SOCKET_INVALID_STATE) {
        std::stringstream msg;
        msg << MSG_SOCKET_ERROR_INVALID_CREATE << " " << sockfd;
        throw SocketError(msg.str());
    }
    this->sockfd = sockfd;
}

int SocketBase::getSockFd(void) const {
    return this->sockfd;
}

void SocketBase::SktClose(void) {
    ::close(this->sockfd);
    this->sockfd = SOCKET_INVALID_STATE;
}

SocketBase::~SocketBase(void) {
    if (this->sockfd != SOCKET_INVALID_STATE) {
        /* std::cout << "Destruyendo socket" << std::endl; */
        ::shutdown(getSockFd(), SHUT_RDWR);
        SktClose();
    }
}

SocketBase::SocketBase(SocketBase && move) noexcept :
 sockfd(SOCKET_INVALID_STATE) {
    int t = this->sockfd;
    this->sockfd = move.sockfd;
    move.sockfd = t;
}

bool SocketBase::validState(void) const {
    return (this->sockfd == SOCKET_INVALID_STATE ? false : true);
}

SocketReadWrite::SocketReadWrite(int sockfd) : SocketBase(sockfd) {
}

size_t SocketReadWrite::getBuffer(uchar * buffer, int size) const {
    if (getSockFd() == SOCKET_INVALID_STATE) {
        std::stringstream msg;
        msg << MSG_SOCKET_ERROR_INVALID_READ << " " << getSockFd();
        throw SocketError(msg.str());        
    }
    bool skt_closed = false;
    int rcv_bytes = 0;
    int rcv_status, remain;
    /* std::cout << "Intentare recibir " << size << " bytes." << std::endl; */
    while (skt_closed == false && rcv_bytes < size) {
        remain = size - rcv_bytes;
        rcv_status = 
        ::recv(getSockFd(), &buffer[rcv_bytes], remain, MSG_NOSIGNAL);
        /* std::cout << "Recibidos " << rcv_status << " bytes." << std::endl; */
        if (rcv_status > 0) {
            rcv_bytes += rcv_status;
        } else if (rcv_status == 0) {
            skt_closed = true;
        } else if (rcv_status == -1) {
            std::stringstream msg;
            msg << MSG_SOCKET_ERROR_READ << " " << rcv_bytes
            << std::strerror(errno);
            throw SocketError(msg.str()); 
        }
    }

    if (rcv_bytes > 0)
        return rcv_bytes;

    if (skt_closed)
        return 0;

    return 0;
}

void SocketReadWrite::sendBuffer(const uchar * buffer, int size) const {
    if (getSockFd() == SOCKET_INVALID_STATE) {
        std::stringstream msg;
        msg << MSG_SOCKET_ERROR_INVALID_WRITE << " " << getSockFd();
        throw SocketError(msg.str());        
    }

    int remain = size;
    int send_status = 0;

    while (remain) {
        send_status = 
        ::send(getSockFd(), &buffer[remain-size], remain, MSG_NOSIGNAL);
        if (send_status == -1) {
            std::stringstream msg;
            msg << MSG_SOCKET_ERROR_WRITE << " " << size-remain
            << std::strerror(errno);
            throw SocketError(msg.str()); 
        } else { 
            remain -= send_status;
        }
    }
}

void SocketReadWrite::shutDown(void) {
    int errcode = 0;
    /* std::cout << "Haciendo el shutdown en la clase socket." << std::endl; */
    errcode = ::shutdown(getSockFd(), SHUT_RDWR);
    /* std::cout << "Shutdown hecho!" << std::endl; */
    if (errcode) {
        std::stringstream msg;
        /* msg << MSG_SOCKET_ERROR_SHUTDOWN << std::strerror(errno); */
        throw SocketError(msg.str());
    }
}

int SocketConnection::_get_valid_socket
(std::string const & host, std::string const & port) {
    struct ::addrinfo hints;
    memset(&hints, 0, sizeof(struct ::addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    int errcode = 0;
    errcode = ::getaddrinfo
    (host.c_str(), port.c_str(), &hints, &this->results);
    if (errcode) {
        std::stringstream msg;
        msg << MSG_SOCKET_ERROR_ADDRINFO << std::strerror(errno);
        throw SocketError(msg.str());    
    }

    errcode = 0;
    int newsockfd = -1;

    for (this->result = this->results; 
    this->result != NULL; 
    this->result = this->result->ai_next) {
        newsockfd = ::socket
        (this->result->ai_family, this->result->ai_socktype,
         this->result->ai_protocol);
        if (newsockfd == -1) {
            continue;
        } else {
            break;
        }
    }
    return newsockfd;
}

SocketConnection::SocketConnection
(std::string const & host, std::string const & port)
 : SocketReadWrite(_get_valid_socket(host, port)) {
    int errcode = 
    ::connect(getSockFd(), this->result->ai_addr, this->result->ai_addrlen);
    ::freeaddrinfo(this->results);
    this->result = NULL;
    this->results = NULL;

    if (errcode == -1) {
        SktClose();
        std::stringstream msg;
        msg << MSG_SOCKET_ERROR_CONNECT << " " << host << " " << port;
        throw SocketError(msg.str());  
    }
}

int SocketListener::_get_valid_socket_listener(std::string const & port) {
    struct ::addrinfo hints;

    memset(&hints, 0, sizeof(struct ::addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; 

    int errcode = 0;
    errcode = ::getaddrinfo(NULL, port.c_str(), &hints, &this->result);
    if (errcode) {
        std::stringstream msg;
        msg << MSG_SOCKET_ERROR_ADDRINFO << std::strerror(errno);
        throw SocketError(msg.str());  
    }

    return ::socket(this->result->ai_family, this->result->ai_socktype,
    this->result->ai_protocol);
}

SocketListener::SocketListener(std::string const & port) :
SocketBase(_get_valid_socket_listener(port)){
    int skopt = 1;
    ::setsockopt(getSockFd(), SOL_SOCKET, SO_REUSEADDR, &skopt, sizeof(skopt));

    int errcode = 
    ::bind(getSockFd(), this->result->ai_addr, this->result->ai_addrlen);
    if (errcode == -1) {
        SktClose();
        std::stringstream msg;
        msg << MSG_SOCKET_ERROR_BIND << " "
        << port << ". " << std::strerror(errno);
        throw SocketError(msg.str());  
    }

    ::freeaddrinfo(this->result);
    this->result = NULL;

    errcode = ::listen(getSockFd(), SOCKET_LISTENER_MAX_CONNECTION_WAITING);
    if (errcode == -1) {
        SktClose();
        std::stringstream msg;
        msg << MSG_SOCKET_ERROR_LISTEN << " " 
        << port << ". " << std::strerror(errno);
        throw SocketError(msg.str());  
    }
}

SocketReadWrite SocketListener::accept_connection(void) {
    if (getSockFd() == SOCKET_INVALID_STATE) {
        std::stringstream msg;
        msg << MSG_SOCKET_ERROR_ACCEPT_INVALID;
        throw SocketError(msg.str());
    }

    int newsockfd = ::accept(getSockFd(), NULL, NULL);
    if (newsockfd == -1) {
        std::stringstream msg;
        msg << MSG_SOCKET_ERROR_ACCEPT << " " << std::strerror(errno);
        throw SocketError(msg.str());    
    }

    return std::move(SocketReadWrite(newsockfd));
}

void SocketListener::stopListening(void) {
    int errcode = 0;
    errcode = ::shutdown(getSockFd(), SHUT_RDWR);
    if (errcode) {
        std::stringstream msg;
        msg << MSG_SOCKET_ERROR_SHUTDOWN << std::strerror(errno);
        throw SocketError(msg.str());
    }
}
