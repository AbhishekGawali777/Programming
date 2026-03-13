#include "server.h"
#include "router.h"

CRouter router;

int main() {
    router.addRoute("/", [](){
        return "<h1>Welcome to High Performance C++ Server</h1>";
    });

    router.addRoute("/", [](){
        return "<h1>About Page</h1>";
    });

    // 8 Threads at server
    CHttpServer server(8080, 8);

    // We are good to start server...
    server.start();
}