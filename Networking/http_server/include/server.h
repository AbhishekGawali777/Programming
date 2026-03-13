#ifndef _SERVER_H__
#define _SERVER_H__

class CHttpServer {

    int port;
    int server_fd;

    public:
    
    CHttpServer(int port, int threads);

    void start();
};

#endif  // _SERVER_H__
