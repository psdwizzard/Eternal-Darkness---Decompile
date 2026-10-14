typedef struct OSThread OSThread;

typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

void OSInitThreadQueue(OSThreadQueue *queue)
{
    queue->head = queue->tail = 0;
}
