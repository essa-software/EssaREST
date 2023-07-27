#pragma once
#include <EssaUtil/UString.hpp>
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "BasicServer.hpp"
#include "../rest/HttpServerResponse.hpp"

class HttpServer : public BasicServer {
public:
    HttpServer() = default;

    virtual void run();
    void add_get_method(const std::string uri, std::function<HttpServerResponse(HttpServerResponse&)> foo);
};