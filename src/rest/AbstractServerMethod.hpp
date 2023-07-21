#pragma once

#include "AbstractClientRequest.hpp"
class AbstractServerMethod{
public:
    AbstractServerMethod() = default;
    virtual void exec(AbstractClientRequest*){}
    virtual ~AbstractServerMethod() = default;
};
