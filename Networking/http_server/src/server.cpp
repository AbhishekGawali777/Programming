#include "server.h"
#include "event_loop.h"
#include "thread_pool.h"
#include "connection_handler.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

CHttpServer::CHttpServer(int port, int threads) {
    this->port = port;
}

void CHttpServer::start() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));

    listen(server_fd, 1024);

    CEventLoop loop;

    loop.addDescriptor(server_fd);

    CThreadPool pool(std::thread::hardware_concurrency());

    struct kevent events[1024];

    while(true) {
        int n = loop.wait(events, 1024);

        for(int i = 0; i < n; ++i) {
            int fd = (int)events[i].ident;

            // Server Descriptor matched
            if(fd == server_fd) {

                // Accept the connection
                int client = accept(server_fd, nullptr, nullptr);
                
                // add descriptor of client to Eventloop
                loop.addDescriptor(client);
            }
            else 
            {
                pool.enqueue([fd]{
                    CConnection::handle(fd);
                });
            }
        }
    }
}