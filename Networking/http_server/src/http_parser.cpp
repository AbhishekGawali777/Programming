#include "http_parser.h"
#include <sstream>

HttpRequest CHttpParser::parse(const std::string& request) {
    std::stringstream ss(request);

    HttpRequest req;

    ss >> req.method;
    ss >> req.path;
    ss >> req.version;

    return req;
}
