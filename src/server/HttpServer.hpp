#pragma once
#include <EssaUtil/UString.hpp>
#include <cstdint>
#include <map>
#include <vector>
#include "BasicServer.hpp"

class HttpServer : public BasicServer {
public:
    HttpServer() = default;

    virtual void run();

    virtual ~HttpServer() = default;
};