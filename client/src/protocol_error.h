#ifndef __PROTOCOL_ERROR_H__
#define __PROTOCOL_ERROR_H__

#include <exception>
#include <string>

/*
Clase para generar excepciones del tipo 'protocol'.
*/
class ProtocolError : public std::exception {
    private:
        std::string msg;
    public:
        explicit ProtocolError(const std::string &);
        virtual const char * what(void) const noexcept;
        virtual ~ProtocolError(void) noexcept;
};

#endif
