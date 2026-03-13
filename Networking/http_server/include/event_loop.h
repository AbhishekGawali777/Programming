#ifndef _EVENT_LOOP_H__
#define _EVENT_LOOP_H__

#include <sys/event.h>

class CEventLoop {
    public:

    CEventLoop();

    void addDescriptor(int fd);

    int wait(struct kevent* events, int max_events);

    private:

    int pool_fd;
};

#endif // _EVENT_LOOP_H__
