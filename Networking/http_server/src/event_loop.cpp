#include "event_loop.h"
#include <unistd.h>
#include <iostream>

CEventLoop::CEventLoop() {
    pool_fd = kqueue();
}

void CEventLoop::addDescriptor(int fd) {
    struct kevent event;

    EV_SET(&event, pool_fd, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, NULL);

    if(kevent(pool_fd, &event, 1, NULL, 0, NULL)) {
        std::cout << "kevent registration Failed" << std::endl;
    }
}

int CEventLoop::wait(struct kevent* events, int max_events) {
    int nEvents = kevent(pool_fd, NULL, 0, events, max_events, NULL);

    return nEvents;
}
