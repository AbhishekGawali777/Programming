#include <iostream>
#include <thread>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>

const char* SERVER_IP = "127.0.0.1";
const int PORT = 8080;

void SendRequest() {

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    inet_pton(AF_INET, SERVER_IP, &server.sin_addr);

    if(connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cout << "Connecting Server Failed" << std::endl;
        return;
    }

    std::string request =
        "GET / HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Connection: close\r\n"
        "\r\n";

    send(sock, request.c_str(), request.size(), 0);

    char buffer[2048];

    while(recv(sock, buffer, sizeof(buffer), 0) > 0)    

    close(sock);
} 

int main(int argc, char** argv) {

    int threads = 100;
    int request_per_thread = 100;

    std::vector<std::thread> workers;

    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < threads; ++i) {
        workers.emplace_back([=]() {
            for(int j = 0; j < request_per_thread; ++j) {
                SendRequest();
            }
        });
    }

    for(auto &t : workers) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();

    double seconds = std::chrono::duration<double>(end - start).count();

    int total_requests = threads * request_per_thread;

    std::cout << "Total Requests: " << total_requests << std::endl;
    std::cout << "Time: " << seconds << "Seconds" << std::endl;

    std::cout << "Requests/sec: " << total_requests / seconds << std::endl;

}