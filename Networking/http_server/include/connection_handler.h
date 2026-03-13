#ifndef _CONNECTION_HANDLER_H__
#define _CONNECTION_HANDLER_H__

#include <string>

class CConnection {
    public:

    static void handle(int client_fd);
};

#endif // _CONNECTION_HANDLER_H__
