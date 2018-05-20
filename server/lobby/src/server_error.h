#ifndef __SERVER_ERROR_H__
#define __SERVER_ERROR_H__

#include <exception>
#include <iostream>
#include <string>

/*
Clase para generar excepciones del tipo 'servidor'.
*/
class ServerError : public std::exception {
    private:
        std::string msg;
    public:
        explicit ServerError(const std::string &);
        virtual const char * what() const noexcept;
        virtual ~ServerError() noexcept;
};

#endif
