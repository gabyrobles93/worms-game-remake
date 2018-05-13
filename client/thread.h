#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <thread>

/*
Clase abstracta que encapsula un thread. La idea es que los objetos vivos hereden de esta clase e implementen los metodos virtuales run() (el mas importante,
ya que 'dispara' el thread), isRunning (que sirve para saber cuando un thread termino de ejecutarse), y getId (esto si deseamos que cada thread tenga un
ID unico, quiza con fines de debugging).
*/
class Thread {
    private:
        std::thread thread;
    public:
        Thread(void);
        Thread(Thread &&);
        Thread & operator=(Thread && other);
        virtual ~Thread(void);
        virtual void run(void) = 0;
        virtual bool isRunning(void) const = 0;
        virtual size_t getId(void) const = 0;
        void join(void);
        void start(void);
        Thread(const Thread &) = delete;
        Thread & operator=(const Thread &) = delete;
};

#endif
