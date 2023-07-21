#pragma once

#include <map>
#include <string>
#include <utility>
#include "Defines.hpp"

class AbstractClientRequest{    
public:
    AbstractClientRequest() = default;
    virtual HttpResponseCode parse(const char* req) = 0;

    virtual ~AbstractClientRequest() = default;
};
