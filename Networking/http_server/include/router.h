#ifndef _ROUTER_H__
#define _ROUTER_H__

#include <unordered_map>
#include <string>
#include <functional>


class CRouter {
    public:

    using Handler = std::function<std::string()>;
    void addRoute(const std::string& path, Handler handler);
    std::string handle(const std::string& path);

    private:

    std::unordered_map<std::string, Handler> routes;
};

#endif // _ROUTER_H__
