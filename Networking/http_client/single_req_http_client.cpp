#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {

    const char* server_ip = "127.0.0.1";
    const int port = 8080;
    
    // Initialize socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0) {
        std::cerr << "Socket Creation Failed" << std::endl;
        return -1;
    }

    // Initialize server information to be connected
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    inet_pton(AF_INET, server_ip, &server.sin_addr);

    // Connect to the server
    if(connect(sock, (sockaddr*)& server, sizeof(server) < 0)) {
        std::cerr << "connection failed" << std::endl;
        return -1;
    }

    std::string request = 
        "Get / HTTP /1.1/r/n"
        "Host: localhost\r\n"
        "Connection: close\r\n"
        "\r\n";

    send(sock, request.c_str(), request.size(), 0);

    char buffer[4096];

    while (true) {

        int bytes = recv(sock, buffer, sizeof(buffer), 0);

        if(bytes <= 0)
            break;

        std::cout.write(buffer, bytes);
    }

    close(sock);

    return 0;
}
