#ifndef __COMMON_SOCKET_H__
#define __COMMON_SOCKET_H__

#include <string>

#define SOCKET_INVALID_STATE -1
#define SOCKET_INITIAL_STATE 0
#define SOCKET_LISTENER_MAX_CONNECTION_WAITING 10

#define MSG_SOCKET_ERROR_INVALID_CREATE "Se intenta crear un socket invalido."
#define MSG_SOCKET_ERROR_INVALID_READ "Se intenta leer un socket invalido."
#define MSG_SOCKET_ERROR_READ "-1 en recv() de socket tras recibir (bytes):"
#define MSG_SOCKET_ERROR_INVALID_WRITE "Escritura en un socket invalido."
#define MSG_SOCKET_ERROR_WRITE "-1 en send() de socket tras enviar (bytes):"
#define MSG_SOCKET_ERROR_SHUTDOWN "Error en shutdown de socket:"
#define MSG_SOCKET_ERROR_ADDRINFO "Error en socket getaddrinfo():"
#define MSG_SOCKET_ERROR_CONNECT "No se pudo conectar socket TCP al ip-port:"
#define MSG_SOCKET_ERROR_BIND "Error en bind de socket en puerto: "
#define MSG_SOCKET_ERROR_LISTEN "Error en listen() de socket en puerto:"
#define MSG_SOCKET_ERROR_ACCEPT_INVALID "accept() en un socket invalido."
#define MSG_SOCKET_ERROR_ACCEPT "Error de socket tras un accept():"

typedef struct addrinfo net_addrinfo;
typedef unsigned char uchar;

/*
Base para cualquier tipo de socket. Contiene el file descriptor y funciones basicas para cualquier socket como
un constructor (por parametro y por movimiento), destructor, cierre y pregunta si esta en estado valido (fd != -1).
No es valido copiar un socket, por lo que dichos metodos estan anulados. Cualquier tipo de socket heredara de este
socket base.
*/
class SocketBase {
    private:
    
    protected:
        explicit SocketBase(int fd);
        int getSockFd(void) const;

    public:
        int sockfd;
        SocketBase(SocketBase && move) noexcept;
        virtual ~SocketBase(void);
        void SktClose(void);
        bool validState(void) const;
        explicit SocketBase(SocketBase const&) = delete;
        SocketBase& operator=(SocketBase const&) = delete;
};

/*
Este tipo de socket es un socket que ya esta conectado con un par y tiene los metodos para enviar y recibir buffers de informacion.
Tambien puede hacer shutdown para indicarle al par que termino de operar. Su consturctor llama al constructor base, pasandole un file
descriptor valido.
*/
class SocketReadWrite : public SocketBase {
    private:
    protected:
    public:
        explicit SocketReadWrite(int sockfd);
        size_t getBuffer(uchar * buffer, int size) const;
        void sendBuffer(const uchar * buffer, int size) const;
        void shutDown(void);
};

/*
Este tipo de socket se construira exitosamente cuando pueda conectarse al IP-PORT que se pasen como parametro. Hereda de
SocketReadWrite por lo que una vez construido (y conectado) puede enviar y recibir informacion con su par.
Su metodo _get_valid_socket() itera en los addr results buscando una conexion valida, y retorna un file descriptor valido,
luego SocketConnection invoca al constructor de su padre con dicho file descriptor valido, y posteriormente se conecta con el par.
*/
class SocketConnection : public SocketReadWrite {
    private:
        net_addrinfo * result;
        net_addrinfo * results;
        int _get_valid_socket(std::string const &, std::string const &);
    protected:
    public:
        SocketConnection(std::string const &, std::string const &);
};

/*
Este tipo de socket representa un 'socket listener' o 'socket aceptador', propio de un servidor. Con la macro SOCKET_LISTENER_MAX_CONNECTION_WAITING
se definen la cantidad de conexiones en espera que puede tener. Una vez construido este socket, queda escuchando conexiones en <port>. El metodo
accept_connection() es bloqueante y espera una nueva conexion. Al recibir una conexion, retorna con move semantics un socket del tipo SocketReadWrite,
que esta listo para enviar y recibir datos con su par.
*/
class SocketListener : public SocketBase {
    private:
        net_addrinfo * result;
        size_t max_connections_waiting = 
        SOCKET_LISTENER_MAX_CONNECTION_WAITING;
        int _get_valid_socket_listener(std::string const &);
    protected:
    public:
        explicit SocketListener(std::string const & port);
        SocketReadWrite accept_connection(void);
        void stopListening(void);
};


#endif
