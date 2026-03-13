#ifndef _HTTP_PARSER_H__
#define _HTTP_PARSER_H__

#include <string>

struct HttpRequest
{
    std::string method;
    std::string path;
    std::string version;
};

class CHttpParser {
    public:
    static HttpRequest parse(const std::string& request);
};

#endif // _HTTP_PARSER_H__
