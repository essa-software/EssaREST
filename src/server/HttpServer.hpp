#pragma once
#include <EssaUtil/UString.hpp>
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "BasicServer.hpp"

class HttpServer : public BasicServer {
public:
    HttpServer() = default;

    virtual void run();
    // void add_post_method(const std::string& uri, )

    virtual ~HttpServer() = default;
};