#include "model_sender.h"
#include "blocking_queue.h"
#include "thread.h"
#include "protocol.h"

ModelSender::ModelSender(Protocol & p, BlockingQueue<char> & q) :
protocol(p),
queue(q)
{
}
