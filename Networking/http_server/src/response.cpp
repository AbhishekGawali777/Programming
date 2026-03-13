#include "response.h"
#include <sstream>

std::string CHttpResponse::build(const std::string& body) {
    std::stringstream ss;

    ss << "HTTP/1.1 200 OK\r\n";
    ss << "Content-Type: text/html\r\n";
    ss << "Content-Length: keep-alive\r\n";
    ss <<  "\r\n";
    ss << body;

    return ss.str();
}