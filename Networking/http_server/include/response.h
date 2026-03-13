#ifndef _RESPONSE_H__
#define _RESPONSE_H__

#include <string>

class CHttpResponse {

    public:

    static std::string build(const std::string& body);
};

#endif // _RESPONSE_H__
