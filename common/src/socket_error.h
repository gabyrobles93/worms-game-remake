#ifndef __COMMON_SOCKET_ERROR_H__
#define __COMMON_SOCKET_ERROR_H__

#include <exception>
#include <string>

/*
Clase para generar excepciones del tipo 'socket'.
*/
class SocketError : public std::exception {
    private:
        std::string msg;
    public:
        explicit SocketError(const std::string &);
        virtual const char * what(void) const noexcept;
        virtual ~SocketError(void) noexcept;
};

#endif
