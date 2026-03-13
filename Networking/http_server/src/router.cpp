#include "router.h"

void CRouter::addRoute(const std::string& path, Handler handler) {
    routes[path] = handler;
}

std::string CRouter::handle(const std::string& path) {
    if(routes.count(path))
        return routes[path]();

    return "<h1>404 not found</h1>";
}