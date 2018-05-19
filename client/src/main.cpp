#include <iostream>
#include <fstream>
#include <unistd.h>
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"
#include "protocol_error.h"
#include "thread.h"
#include "blocking_queue.h"
#include "yaml.h"
#include "event_sender.h"
#include "model_receiver.h"

#define CONNECTION_HOST "localhost"
#define CONNECTION_PORT "8080"

int main(/* int argc, char *argv[] */)
try {
    BlockingQueue<char> events;
    char model;
    Protocol protocol(SocketConnection(CONNECTION_HOST, CONNECTION_PORT));
    EventSender event_sender(protocol, events);
    ModelReceiver model_receiver(protocol, model);

    event_sender.start();
    model_receiver.start();

    char c;
    do {
        c = getchar();  // UN EVENTO ME GENERA UN MENSAJE PARA EL SERVIDOR
        events.push(c); // AGREGAMOS EL MENSAJE A LA COLA QUE TOMA EL HILO QUE ENVIA AL SERVIDOR
 //       draw(model);    // DIBUJAMOS EL MODELO (TOMANDO LOCK) QUE FUE EDITADO POR EL HILO QUE RECIBE MODELOS DEL SERVIDOR
    } while (c != 'q');

    event_sender.stop();
    event_sender.join();
    model_receiver.stop();
    model_receiver.join();

} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}
