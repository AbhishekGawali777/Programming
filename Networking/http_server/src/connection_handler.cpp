#include "connection_handler.h"
#include "http_parser.h"
#include "response.h"
#include "router.h"

#include <unistd.h>
#include <sys/socket.h>

extern CRouter router;

void CConnection::handle(int client_fd) {
    char buffer[4096];

    int bytes = read(client_fd, buffer, sizeof(buffer));

    if(bytes <= 0) {
        close(client_fd);
        return;
    }

    const std::string req(buffer, bytes);

    HttpRequest request = CHttpParser::parse(req);

    std::string body = router.handle(request.path);

    std::string response = CHttpResponse::build(body);

    int bytes_sent = send(client_fd, response.c_str(), response.size(), 0);

    if (bytes_sent == -1) {
        perror("send failed");
    }

}
